#include "roboticfluid_cpp/rf_owner/nested/owner_v3.hpp"
#include "roboticfluid_cpp/common.hpp"
#include <cstring>
#include <string>
#include <vector>

namespace rf_owner {
namespace nested {

void OwnerV3::dump(std::vector<uint8_t>& out) const {
    size_t old_size = out.size();
    if (out.capacity() - out.size() < sizeof(OwnerV3))
        out.reserve(out.size() + sizeof(OwnerV3));
    out.resize(old_size + sizeof(OwnerV3));
    std::memcpy(out.data() + old_size, this, sizeof(OwnerV3));
    // Call dump_dynamic_only to handle the dynamic parts
    dump_dynamic_only(out);
}

void OwnerV3::load(const std::vector<uint8_t>& src) {
    size_t offset = 0;
    load(src, offset);
}

} // namespace nested
} // namespace rf_owner 