#include "roboticfluid_cpp/rf_owner/owner.hpp"
#include "roboticfluid_cpp/common.hpp"
#include <cstring>
#include <string>
#include <vector>

namespace rf_owner {

void Owner::dump(std::vector<uint8_t>& out) const {
    size_t old_size = out.size();
    if (out.capacity() - out.size() < sizeof(Owner))
        out.reserve(out.size() + sizeof(Owner));
    out.resize(old_size + sizeof(Owner));
    std::memcpy(out.data() + old_size, this, sizeof(Owner));
    // Call dump_dynamic_only to handle the dynamic parts
    dump_dynamic_only(out);
}

void Owner::load(const std::vector<uint8_t>& src) {
    size_t offset = 0;
    load(src, offset);
}

} // namespace rf_owner