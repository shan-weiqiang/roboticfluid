#include "roboticfluid_cpp/rf_owner/owner_v2.hpp"
#include "roboticfluid_cpp/common.hpp"
#include <cstring>
#include <string>
#include <vector>

namespace rf_owner {

void OwnerV2::dump(std::vector<uint8_t>& out) const {
    size_t old_size = out.size();
    if (out.capacity() - out.size() < sizeof(OwnerV2))
        out.reserve(out.size() + sizeof(OwnerV2));
    out.resize(old_size + sizeof(OwnerV2));
    std::memcpy(out.data() + old_size, this, sizeof(OwnerV2));
    // Call dump_dynamic_only to handle the dynamic parts
    dump_dynamic_only(out);
}

void OwnerV2::load(const std::vector<uint8_t>& src) {
    size_t offset = 0;
    load(src, offset);
}

} // namespace rf_owner 