#include "roboticfluid_cpp/owner_v4.hpp"
#include "roboticfluid_cpp/common.hpp"
#include <cstring>
#include <string>

void OwnerV4::dump(std::vector<uint8_t>& out) const {
    size_t old_size = out.size();
    if (out.capacity() - out.size() < sizeof(OwnerV4))
        out.reserve(out.size() + sizeof(OwnerV4));
    out.resize(old_size + sizeof(OwnerV4));
    std::memcpy(out.data() + old_size, this, sizeof(OwnerV4));
    // Call dump_dynamic_only to handle the dynamic parts
    dump_dynamic_only(out);
}

void OwnerV4::load(const std::vector<uint8_t>& src) {
    size_t offset = 0;
    load(src, offset);
} 