#pragma once
#include <string>
#include <cstdint>
#include <cstring>
#include <vector>
#include <array>
#include <lz4.h>

namespace rf_common {

// Variable-length integer encoding (similar to protobuf varint)
inline void write_varint(std::vector<uint8_t> &out, uint32_t value) {
    while (value >= 0x80) {
        out.push_back(static_cast<uint8_t>((value & 0x7F) | 0x80));
        value >>= 7;
    }
    out.push_back(static_cast<uint8_t>(value & 0x7F));
}

inline void read_varint(const std::vector<uint8_t> &src, size_t &offset, uint32_t &value) {
    value = 0;
    int shift = 0;
    while (offset < src.size()) {
        uint8_t byte = src[offset++];
        value |= static_cast<uint32_t>(byte & 0x7F) << shift;
        if ((byte & 0x80) == 0) break;
        shift += 7;
    }
}

// Optimized string serialization with varint length
inline void write_string_optimized(std::vector<uint8_t> &out, const std::string &s) {
    write_varint(out, static_cast<uint32_t>(s.size()));
    out.insert(out.end(), s.begin(), s.end());
}

inline void read_string_optimized(const std::vector<uint8_t> &src, size_t &offset, std::string &s) {
    uint32_t len = 0;
    read_varint(src, offset, len);
    s.assign(reinterpret_cast<const char*>(src.data() + offset), len);
    offset += len;
}

// Optimized vector serialization with varint size
template<typename T>
inline void write_vector_optimized(std::vector<uint8_t> &out, const std::vector<T> &vec) {
    write_varint(out, static_cast<uint32_t>(vec.size()));
    if (!vec.empty()) {
        out.insert(out.end(), reinterpret_cast<const uint8_t*>(vec.data()), 
                  reinterpret_cast<const uint8_t*>(vec.data()) + vec.size() * sizeof(T));
    }
}

template<typename T>
inline void read_vector_optimized(const std::vector<uint8_t> &src, size_t &offset, std::vector<T> &vec) {
    uint32_t sz = 0;
    read_varint(src, offset, sz);
    vec.resize(sz);
    if (sz > 0) {
        size_t bytes_needed = static_cast<size_t>(sz) * sizeof(T);
        std::memcpy(vec.data(), src.data() + offset, bytes_needed);
        offset += bytes_needed;
    }
}

// Optimized fixed-size array serialization (no size prefix needed)
template<typename T, size_t N>
inline void write_fixed_array_optimized(std::vector<uint8_t> &out, const std::array<T, N> &arr) {
    out.insert(out.end(), reinterpret_cast<const uint8_t*>(arr.data()), 
              reinterpret_cast<const uint8_t*>(arr.data()) + N * sizeof(T));
}

template<typename T, size_t N>
inline void read_fixed_array_optimized(const std::vector<uint8_t> &src, size_t &offset, std::array<T, N> &arr) {
    std::memcpy(arr.data(), src.data() + offset, N * sizeof(T));
    offset += N * sizeof(T);
}

// Helper to write a length-prefixed string (original for backward compatibility)
inline void write_string(std::vector<uint8_t> &out, const std::string &s) {
    uint32_t len = static_cast<uint32_t>(s.size());
    out.insert(out.end(), reinterpret_cast<const uint8_t*>(&len), reinterpret_cast<const uint8_t*>(&len) + sizeof(len));
    out.insert(out.end(), s.begin(), s.end());
}

// Helper to read a length-prefixed string (original for backward compatibility)
inline void read_string(const std::vector<uint8_t> &src, size_t &offset, std::string &s) {
    uint32_t len = 0;
    std::memcpy(&len, src.data() + offset, sizeof(len));
    offset += sizeof(len);
    s.assign(reinterpret_cast<const char*>(src.data() + offset), len);
    offset += len;
}

// LZ4 compression wrapper
inline std::vector<uint8_t> compress_lz4(const std::vector<uint8_t>& data) {
    if (data.empty()) {
        return {};
    }
    
    // Calculate maximum compressed size
    int max_compressed_size = LZ4_compressBound(static_cast<int>(data.size()));
    std::vector<uint8_t> compressed(max_compressed_size);
    
    // Compress the data
    int compressed_size = LZ4_compress_default(
        reinterpret_cast<const char*>(data.data()),
        reinterpret_cast<char*>(compressed.data()),
        static_cast<int>(data.size()),
        max_compressed_size
    );
    
    if (compressed_size <= 0) {
        // Compression failed, return original data
        return data;
    }
    
    // Resize to actual compressed size
    compressed.resize(compressed_size);
    return compressed;
}

// LZ4 decompression wrapper
inline std::vector<uint8_t> decompress_lz4(const std::vector<uint8_t>& compressed_data, size_t original_size) {
    if (compressed_data.empty()) {
        return {};
    }
    
    std::vector<uint8_t> decompressed(original_size);
    
    // Decompress the data
    int decompressed_size = LZ4_decompress_safe(
        reinterpret_cast<const char*>(compressed_data.data()),
        reinterpret_cast<char*>(decompressed.data()),
        static_cast<int>(compressed_data.size()),
        static_cast<int>(original_size)
    );
    
    if (decompressed_size <= 0) {
        // Decompression failed, return empty vector
        return {};
    }
    
    // Resize to actual decompressed size
    decompressed.resize(decompressed_size);
    return decompressed;
}

// Compressed serialization wrapper
template<typename T>
inline void dump_compressed(const T& obj, std::vector<uint8_t>& out) {
    // First serialize normally
    std::vector<uint8_t> serialized;
    obj.dump(serialized);
    
    // Then compress
    std::vector<uint8_t> compressed = compress_lz4(serialized);
    
    // Prepend the original size to the compressed data
    write_varint(out, static_cast<uint32_t>(serialized.size()));
    out.insert(out.end(), compressed.begin(), compressed.end());
}

// Compressed deserialization wrapper
template<typename T>
inline bool load_compressed(T& obj, const std::vector<uint8_t>& compressed_data) {
    if (compressed_data.empty()) {
        return false;
    }
    
    // Extract the original size from the beginning
    size_t offset = 0;
    uint32_t original_size;
    read_varint(compressed_data, offset, original_size);
    
    // Extract the actual compressed data
    std::vector<uint8_t> actual_compressed_data(
        compressed_data.begin() + offset, 
        compressed_data.end()
    );
    
    // First decompress
    std::vector<uint8_t> decompressed = decompress_lz4(actual_compressed_data, original_size);
    
    if (decompressed.empty()) {
        return false; // Decompression failed
    }
    
    // Then deserialize
    try {
        obj.load(decompressed);
        return true;
    } catch (...) {
        return false; // Deserialization failed
    }
}

} // namespace rf_common 