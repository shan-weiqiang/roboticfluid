#pragma once

#include <string>
#include <vector> // Added for std::vector
#include <cstring> // Added for std::memcpy
#include "roboticfluid_cpp/common.hpp"

namespace rf_owner {

class OwnerV2 {
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
  inline size_t load(const std::vector<uint8_t>& src, size_t& offset) {
    this->~OwnerV2();
    std::memcpy(this, src.data() + offset, sizeof(OwnerV2));
    offset += sizeof(OwnerV2);
    std::string name_tmp;
    rf_common::read_string(src, offset, name_tmp);
    new (&name) std::string(std::move(name_tmp));
    return offset;
  }
  void load(const std::vector<uint8_t>& src);
};

} // namespace rf_owner 