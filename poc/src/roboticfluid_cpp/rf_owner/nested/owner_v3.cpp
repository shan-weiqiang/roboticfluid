#include "roboticfluid_cpp/rf_owner/nested/owner_v3.hpp"
#include "roboticfluid_cpp/common.hpp"
#include <cstring>
#include <string>

namespace rf_owner {
namespace nested {

std::string OwnerV3::dump() const {
  std::string out(sizeof(OwnerV3), '\0');
  std::memcpy(&out[0], this, sizeof(OwnerV3));
  rf_common::write_string(out, name);
  return out;
}

size_t OwnerV3::load(const std::string &src) {
  this->~OwnerV3();
  std::memcpy(this, src.data(), sizeof(OwnerV3));
  size_t offset = sizeof(OwnerV3);
  std::string name_tmp;
  rf_common::read_string(src, offset, name_tmp);
  new (&name) std::string(std::move(name_tmp));
  return offset;
}

} // namespace nested
} // namespace rf_owner 