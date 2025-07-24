#include "roboticfluid_cpp/owner_v4.hpp"
#include "roboticfluid_cpp/common.hpp"
#include <cstring>
#include <string>

std::string OwnerV4::freeze() const {
  std::string out(sizeof(OwnerV4), '\0');
  std::memcpy(&out[0], this, sizeof(OwnerV4));
  rf_common::write_string(out, name);
  return out;
}

size_t OwnerV4::melt(const std::string &src) {
  this->~OwnerV4();
  std::memcpy(this, src.data(), sizeof(OwnerV4));
  size_t offset = sizeof(OwnerV4);
  std::string name_tmp;
  rf_common::read_string(src, offset, name_tmp);
  new (&name) std::string(std::move(name_tmp));
  return offset;
} 