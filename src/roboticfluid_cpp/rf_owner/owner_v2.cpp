#include "roboticfluid_cpp/rf_owner/owner_v2.hpp"
#include "roboticfluid_cpp/common.hpp"
#include <cstring>
#include <string>

namespace rf_owner {

std::string OwnerV2::freeze() const {
  std::string out(sizeof(OwnerV2), '\0');
  std::memcpy(&out[0], this, sizeof(OwnerV2));
  rf_common::write_string(out, name);
  return out;
}

size_t OwnerV2::melt(const std::string &src) {
  this->~OwnerV2();
  std::memcpy(this, src.data(), sizeof(OwnerV2));
  size_t offset = sizeof(OwnerV2);
  std::string name_tmp;
  rf_common::read_string(src, offset, name_tmp);
  new (&name) std::string(std::move(name_tmp));
  return offset;
}

} // namespace rf_owner 