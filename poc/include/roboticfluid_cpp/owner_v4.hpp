#pragma once

#include <string>
#include <vector>
#include <cstring>
#include "roboticfluid_cpp/common.hpp"

class OwnerV4 {
public:
  // Data members (public)
  std::string name;
  int age;

  // Getters and Setters
  std::string get_name() const { return name; }
  void set_name(const std::string &val) { name = val; }
  int get_age() const { return age; }
  void set_age(int val) { age = val; }
  void dump(std::vector<uint8_t>& out) const;
  
  // Compressed serialization methods
  void dump_compressed(std::vector<uint8_t>& out) const {
    std::vector<uint8_t> serialized;
    dump(serialized);
    std::vector<uint8_t> compressed = rf_common::compress_lz4(serialized);
    
    // Prepend the original size to the compressed data
    rf_common::write_varint(out, static_cast<uint32_t>(serialized.size()));
    out.insert(out.end(), compressed.begin(), compressed.end());
  }
  
  bool load_compressed(const std::vector<uint8_t>& compressed_data) {
    if (compressed_data.empty()) {
      return false;
    }
    
    // Extract the original size from the beginning
    size_t offset = 0;
    uint32_t original_size;
    rf_common::read_varint(compressed_data, offset, original_size);
    
    // Extract the actual compressed data
    std::vector<uint8_t> actual_compressed_data(
        compressed_data.begin() + offset, 
        compressed_data.end()
    );
    
    // Decompress
    std::vector<uint8_t> decompressed = rf_common::decompress_lz4(actual_compressed_data, original_size);
    if (decompressed.empty()) {
      return false;
    }
    
    try {
      load(decompressed);
      return true;
    } catch (...) {
      return false;
    }
  }
  
  // Internal method for array serialization - only dumps dynamic parts
  inline void dump_dynamic_only(std::vector<uint8_t>& out) const {
    // Only serialize the dynamic parts (std::string name)
    rf_common::write_string_optimized(out, name);
  }
  // Internal method for array deserialization - only loads dynamic parts
  inline size_t load_dynamic_only(const std::vector<uint8_t>& src, size_t& offset) {
    // Only load the dynamic parts (std::string name)
    // The POD parts (age) are already loaded via memcpy
    std::string name_tmp;
    rf_common::read_string_optimized(src, offset, name_tmp);
    new (&name) std::string(std::move(name_tmp));
    return offset;
  }
  inline size_t load(const std::vector<uint8_t>& src, size_t& offset) {
    this->~OwnerV4();
    std::memcpy(this, src.data() + offset, sizeof(OwnerV4));
    offset += sizeof(OwnerV4);
    // Call load_dynamic_only to handle the dynamic parts
    return load_dynamic_only(src, offset);
  }
  void load(const std::vector<uint8_t>& src);
}; 