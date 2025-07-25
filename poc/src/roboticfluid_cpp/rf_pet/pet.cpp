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

    // 2. Serialize all dynamic members in the exact order of appearance
    // 1. std::string s
    rf_common::write_string(out, s);
    // 2. std::array<std::string, 2> arr_s
    for (const auto &s_ : arr_s)
        rf_common::write_string(out, s_);
    // 3. std::vector<double> vec_d
    uint32_t sz = static_cast<uint32_t>(vec_d.size());
    out.insert(out.end(), reinterpret_cast<const uint8_t*>(&sz), reinterpret_cast<const uint8_t*>(&sz) + sizeof(sz));
    if (sz)
        out.insert(out.end(), reinterpret_cast<const uint8_t*>(vec_d.data()), reinterpret_cast<const uint8_t*>(vec_d.data()) + sz * sizeof(vec_d[0]));
    // 4. std::vector<float> vec_f
    sz = static_cast<uint32_t>(vec_f.size());
    out.insert(out.end(), reinterpret_cast<const uint8_t*>(&sz), reinterpret_cast<const uint8_t*>(&sz) + sizeof(sz));
    if (sz)
        out.insert(out.end(), reinterpret_cast<const uint8_t*>(vec_f.data()), reinterpret_cast<const uint8_t*>(vec_f.data()) + sz * sizeof(vec_f[0]));
    // 5. std::vector<int32_t> vec_i32
    sz = static_cast<uint32_t>(vec_i32.size());
    out.insert(out.end(), reinterpret_cast<const uint8_t*>(&sz), reinterpret_cast<const uint8_t*>(&sz) + sizeof(sz));
    if (sz)
        out.insert(out.end(), reinterpret_cast<const uint8_t*>(vec_i32.data()), reinterpret_cast<const uint8_t*>(vec_i32.data()) + sz * sizeof(vec_i32[0]));
    // 6. std::vector<int64_t> vec_i64
    sz = static_cast<uint32_t>(vec_i64.size());
    out.insert(out.end(), reinterpret_cast<const uint8_t*>(&sz), reinterpret_cast<const uint8_t*>(&sz) + sizeof(sz));
    if (sz)
        out.insert(out.end(), reinterpret_cast<const uint8_t*>(vec_i64.data()), reinterpret_cast<const uint8_t*>(vec_i64.data()) + sz * sizeof(vec_i64[0]));
    // 7. std::vector<uint32_t> vec_u32
    sz = static_cast<uint32_t>(vec_u32.size());
    out.insert(out.end(), reinterpret_cast<const uint8_t*>(&sz), reinterpret_cast<const uint8_t*>(&sz) + sizeof(sz));
    if (sz)
        out.insert(out.end(), reinterpret_cast<const uint8_t*>(vec_u32.data()), reinterpret_cast<const uint8_t*>(vec_u32.data()) + sz * sizeof(vec_u32[0]));
    // 8. std::vector<uint64_t> vec_u64
    sz = static_cast<uint32_t>(vec_u64.size());
    out.insert(out.end(), reinterpret_cast<const uint8_t*>(&sz), reinterpret_cast<const uint8_t*>(&sz) + sizeof(sz));
    if (sz)
        out.insert(out.end(), reinterpret_cast<const uint8_t*>(vec_u64.data()), reinterpret_cast<const uint8_t*>(vec_u64.data()) + sz * sizeof(vec_u64[0]));
    // 9. std::vector<bool> vec_bval
    sz = static_cast<uint32_t>(vec_bval.size());
    out.insert(out.end(), reinterpret_cast<const uint8_t*>(&sz), reinterpret_cast<const uint8_t*>(&sz) + sizeof(sz));
    for (auto b : vec_bval) {
        uint8_t bv = b ? 1 : 0;
        out.push_back(bv);
    }
    // 10. std::vector<std::string> vec_s
    sz = static_cast<uint32_t>(vec_s.size());
    out.insert(out.end(), reinterpret_cast<const uint8_t*>(&sz), reinterpret_cast<const uint8_t*>(&sz) + sizeof(sz));
    for (const auto &s_ : vec_s)
        rf_common::write_string(out, s_);
    // 11. rf_owner::Owner own
    own.dump(out);
    // 12. std::array<rf_owner::Owner, 10> arr_own
    for (const auto &o : arr_own)
        o.dump(out);
    // 13. std::vector<rf_owner::Owner> vec_own
    sz = static_cast<uint32_t>(vec_own.size());
    out.insert(out.end(), reinterpret_cast<const uint8_t*>(&sz), reinterpret_cast<const uint8_t*>(&sz) + sizeof(sz));
    for (const auto &o : vec_own)
        o.dump(out);
    // 14. rf_owner::OwnerV2 own_v2
    own_v2.dump(out);
    // 15. std::array<rf_owner::OwnerV2, 10> arr_own_v2
    for (const auto &o : arr_own_v2)
        o.dump(out);
    // 16. std::vector<rf_owner::OwnerV2> vec_own_v2
    sz = static_cast<uint32_t>(vec_own_v2.size());
    out.insert(out.end(), reinterpret_cast<const uint8_t*>(&sz), reinterpret_cast<const uint8_t*>(&sz) + sizeof(sz));
    for (const auto &o : vec_own_v2)
        o.dump(out);
    // 17. rf_owner::nested::OwnerV3 own_v3
    own_v3.dump(out);
    // 18. std::array<rf_owner::nested::OwnerV3, 10> arr_own_v3
    for (const auto &o : arr_own_v3)
        o.dump(out);
    // 19. std::vector<rf_owner::nested::OwnerV3> vec_own_v3
    sz = static_cast<uint32_t>(vec_own_v3.size());
    out.insert(out.end(), reinterpret_cast<const uint8_t*>(&sz), reinterpret_cast<const uint8_t*>(&sz) + sizeof(sz));
    for (const auto &o : vec_own_v3)
        o.dump(out);
    // 20. OwnerV4 own_v4
    own_v4.dump(out);
    // 21. std::array<OwnerV4, 10> arr_own_v4
    for (const auto &o : arr_own_v4)
        o.dump(out);
    // 22. std::vector<OwnerV4> vec_own_v4
    sz = static_cast<uint32_t>(vec_own_v4.size());
    out.insert(out.end(), reinterpret_cast<const uint8_t*>(&sz), reinterpret_cast<const uint8_t*>(&sz) + sizeof(sz));
    for (const auto &o : vec_own_v4)
        o.dump(out);
    // 14. PetType pet_type (POD, handled by block copy)
    // 15. std::array<PetType, 2> arr_pet_type (POD, handled by block copy)
    // 16. std::vector<PetType> vec_pet_type
    sz = static_cast<uint32_t>(vec_pet_type.size());
    out.insert(out.end(), reinterpret_cast<const uint8_t*>(&sz), reinterpret_cast<const uint8_t*>(&sz) + sizeof(sz));
    if (sz)
        out.insert(out.end(), reinterpret_cast<const uint8_t*>(vec_pet_type.data()), reinterpret_cast<const uint8_t*>(vec_pet_type.data()) + sz * sizeof(vec_pet_type[0]));
    // 17. std::array<uint8_t, 100> arr_u8 (POD, handled by block copy)
}

// Convenience overload for top-level load
void Pet::load(const std::vector<uint8_t>& src) {
    size_t offset = 0;
    load(src, offset);
}