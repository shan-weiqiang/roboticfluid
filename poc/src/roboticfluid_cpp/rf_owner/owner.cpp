#include "roboticfluid_cpp/rf_owner/owner.hpp"
#include "roboticfluid_cpp/common.hpp"
#include <cstring>
#include <string>

namespace rf_owner {

std::string Owner::dump() const {
  // Block copy the entire object (shallow copy, including pointer in name)
  std::string out(sizeof(Owner), '\0');
  std::memcpy(&out[0], this, sizeof(Owner));
  // Serialize dynamic member: std::string name
  rf_common::write_string(out, name);
  // int age is POD, already handled by block copy
  return out;
}

size_t Owner::load(const std::string &src) {
  this->~Owner();
  std::memcpy(this, src.data(), sizeof(Owner));
  size_t offset = sizeof(Owner);
  // std::string name
  std::string name_tmp;
  rf_common::read_string(src, offset, name_tmp);
  new (&name) std::string(std::move(name_tmp));
  // int age is POD, already handled by memcpy
  return offset;
}

} // namespace rf_owner