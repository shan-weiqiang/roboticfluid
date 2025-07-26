#pragma once

#include <string>
#include <vector>
#include <cstring>
#include "roboticfluid_cpp/common.hpp"

namespace rf_owner {
namespace nested {

class OwnerV3 {
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
  // Internal method for array serialization - only dumps dynamic parts
  inline void dump_dynamic_only(std::vector<uint8_t>& out) const {
    // Only serialize the dynamic parts (std::string name)
    rf_common::write_string(out, name);
  }
  // Internal method for array deserialization - only loads dynamic parts
  inline size_t load_dynamic_only(const std::vector<uint8_t>& src, size_t& offset) {
    // Only load the dynamic parts (std::string name)
    // The POD parts (age) are already loaded via memcpy
    std::string name_tmp;
    rf_common::read_string(src, offset, name_tmp);
    new (&name) std::string(std::move(name_tmp));
    return offset;
  }
  inline size_t load(const std::vector<uint8_t>& src, size_t& offset) {
    this->~OwnerV3();
    std::memcpy(this, src.data() + offset, sizeof(OwnerV3));
    offset += sizeof(OwnerV3);
    // Call load_dynamic_only to handle the dynamic parts
    return load_dynamic_only(src, offset);
  }
  void load(const std::vector<uint8_t>& src);
};

} // namespace nested
} // namespace rf_owner 