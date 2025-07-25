#pragma once
#include <string>
#include <cstdint>
#include <cstring>
#include <vector>

namespace rf_common {

// Helper to write a length-prefixed string
inline void write_string(std::vector<uint8_t> &out, const std::string &s) {
    uint32_t len = static_cast<uint32_t>(s.size());
    out.insert(out.end(), reinterpret_cast<const uint8_t*>(&len), reinterpret_cast<const uint8_t*>(&len) + sizeof(len));
    out.insert(out.end(), s.begin(), s.end());
}

// Helper to read a length-prefixed string
inline void read_string(const std::vector<uint8_t> &src, size_t &offset, std::string &s) {
    uint32_t len = 0;
    std::memcpy(&len, src.data() + offset, sizeof(len));
    offset += sizeof(len);
    s.assign(reinterpret_cast<const char*>(src.data() + offset), len);
    offset += len;
}

} // namespace rf_common 