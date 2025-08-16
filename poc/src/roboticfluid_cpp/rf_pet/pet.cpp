#include "roboticfluid_cpp/rf_pet/pet.hpp"
#include "roboticfluid_cpp/common.hpp"
#include "roboticfluid_cpp/owner_v4.hpp"
#include <cstring>
#include <new>
#include <string>

using namespace rf_owner;
using namespace rf_pet;

void Pet::dump(std::vector<uint8_t>& out) const {
    // Reserve a reasonable size if you want
    // out.reserve(estimated_size);
    // 1. Block copy the entire object (shallow copy, including pointers in dynamic members)
    size_t old_size = out.size();
    if (out.capacity() - out.size() < sizeof(Pet))
        out.reserve(out.size() + sizeof(Pet));
    out.resize(old_size + sizeof(Pet));
    std::memcpy(out.data() + old_size, this, sizeof(Pet));

    // 2. Call dump_dynamic_only to handle all dynamic members (now optimized)
    dump_dynamic_only(out);
}

// Convenience overload for top-level load
void Pet::load(const std::vector<uint8_t>& src) {
    size_t offset = 0;
    load(src, offset);
}