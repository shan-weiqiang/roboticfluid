#pragma once

#include "../owner_v4.hpp"
#include "../rf_owner/nested/owner_v3.hpp"
#include "../rf_owner/owner.hpp"
#include "../rf_owner/owner_v2.hpp"
#include "pet_type.hpp"
#include <array>
#include <iostream>
#include <string>
#include <vector>

namespace rf_pet {

class Pet {
public:
  // Basic types
  double d;
  float f;
  int32_t i32;
  int64_t i64;
  uint32_t u32;
  uint64_t u64;
  bool bval;
  std::string s;
  // Arrays for each basic type (size 2)
  std::array<double, 2> arr_d;
  std::array<float, 2> arr_f;
  std::array<int32_t, 2> arr_i32;
  std::array<int64_t, 2> arr_i64;
  std::array<uint32_t, 2> arr_u32;
  std::array<uint64_t, 2> arr_u64;
  std::array<bool, 2> arr_bval;
  std::array<std::string, 2> arr_s;
  // Vectors for each basic type
  std::vector<double> vec_d;
  std::vector<float> vec_f;
  std::vector<int32_t> vec_i32;
  std::vector<int64_t> vec_i64;
  std::vector<uint32_t> vec_u32;
  std::vector<uint64_t> vec_u64;
  std::vector<bool> vec_bval;
  std::vector<std::string> vec_s;

  // Custom types
  // Owner
  rf_owner::Owner own;
  std::array<rf_owner::Owner, 10> arr_own;
  std::vector<rf_owner::Owner> vec_own;
  // OwnerV2
  rf_owner::OwnerV2 own_v2;
  std::array<rf_owner::OwnerV2, 10> arr_own_v2;
  std::vector<rf_owner::OwnerV2> vec_own_v2;
  // OwnerV3
  rf_owner::nested::OwnerV3 own_v3;
  std::array<rf_owner::nested::OwnerV3, 10> arr_own_v3;
  std::vector<rf_owner::nested::OwnerV3> vec_own_v3;
  // OwnerV4
  OwnerV4 own_v4;
  std::array<OwnerV4, 10> arr_own_v4;
  std::vector<OwnerV4> vec_own_v4;

  // Enum types
  PetType pet_type;
  // Arrays for enum
  std::array<PetType, 2> arr_pet_type;
  // Vector for enum
  std::vector<PetType> vec_pet_type;

  // New member: array of uint8_t
  std::array<uint8_t, 100> arr_u8;

  // Methods (all public)
  void bark() { std::cout << s << " barks!\n"; }

  // Getters and Setters for basic types
  double get_d() const { return d; }
  void set_d(double val) { d = val; }
  float get_f() const { return f; }
  void set_f(float val) { f = val; }
  int32_t get_i32() const { return i32; }
  void set_i32(int32_t val) { i32 = val; }
  int64_t get_i64() const { return i64; }
  void set_i64(int64_t val) { i64 = val; }
  uint32_t get_u32() const { return u32; }
  void set_u32(uint32_t val) { u32 = val; }
  uint64_t get_u64() const { return u64; }
  void set_u64(uint64_t val) { u64 = val; }
  bool get_bval() const { return bval; }
  void set_bval(bool val) { bval = val; }
  const std::string &get_s() const { return s; }
  void set_s(const std::string &val) { s = val; }
  // Arrays
  const std::array<double, 2> &get_arr_d() const { return arr_d; }
  void set_arr_d(const std::array<double, 2> &val) { arr_d = val; }
  const std::array<float, 2> &get_arr_f() const { return arr_f; }
  void set_arr_f(const std::array<float, 2> &val) { arr_f = val; }
  const std::array<int32_t, 2> &get_arr_i32() const { return arr_i32; }
  void set_arr_i32(const std::array<int32_t, 2> &val) { arr_i32 = val; }
  const std::array<int64_t, 2> &get_arr_i64() const { return arr_i64; }
  void set_arr_i64(const std::array<int64_t, 2> &val) { arr_i64 = val; }
  const std::array<uint32_t, 2> &get_arr_u32() const { return arr_u32; }
  void set_arr_u32(const std::array<uint32_t, 2> &val) { arr_u32 = val; }
  const std::array<uint64_t, 2> &get_arr_u64() const { return arr_u64; }
  void set_arr_u64(const std::array<uint64_t, 2> &val) { arr_u64 = val; }
  const std::array<bool, 2> &get_arr_bval() const { return arr_bval; }
  void set_arr_bval(const std::array<bool, 2> &val) { arr_bval = val; }
  const std::array<std::string, 2> &get_arr_s() const { return arr_s; }
  void set_arr_s(const std::array<std::string, 2> &val) { arr_s = val; }
  // Vectors
  const std::vector<double> &get_vec_d() const { return vec_d; }
  void set_vec_d(const std::vector<double> &val) { vec_d = val; }
  const std::vector<float> &get_vec_f() const { return vec_f; }
  void set_vec_f(const std::vector<float> &val) { vec_f = val; }
  const std::vector<int32_t> &get_vec_i32() const { return vec_i32; }
  void set_vec_i32(const std::vector<int32_t> &val) { vec_i32 = val; }
  const std::vector<int64_t> &get_vec_i64() const { return vec_i64; }
  void set_vec_i64(const std::vector<int64_t> &val) { vec_i64 = val; }
  const std::vector<uint32_t> &get_vec_u32() const { return vec_u32; }
  void set_vec_u32(const std::vector<uint32_t> &val) { vec_u32 = val; }
  const std::vector<uint64_t> &get_vec_u64() const { return vec_u64; }
  void set_vec_u64(const std::vector<uint64_t> &val) { vec_u64 = val; }
  const std::vector<bool> &get_vec_bval() const { return vec_bval; }
  void set_vec_bval(const std::vector<bool> &val) { vec_bval = val; }
  const std::vector<std::string> &get_vec_s() const { return vec_s; }
  void set_vec_s(const std::vector<std::string> &val) { vec_s = val; }

  // Custom type getters/setters
  const rf_owner::Owner &get_own() const { return own; }
  void set_own(const rf_owner::Owner &val) { own = val; }
  void set_arr_own(const std::array<rf_owner::Owner, 10> &val) {
    arr_own = val;
  }
  const std::vector<rf_owner::Owner> &get_vec_own() const { return vec_own; }
  void set_vec_own(const std::vector<rf_owner::Owner> &val) { vec_own = val; }
  const rf_owner::OwnerV2 &get_own_v2() const { return own_v2; }
  void set_own_v2(const rf_owner::OwnerV2 &val) { own_v2 = val; }
  const std::array<rf_owner::OwnerV2, 10> &get_arr_own_v2() const {
    return arr_own_v2;
  }
  void set_arr_own_v2(const std::array<rf_owner::OwnerV2, 10> &val) {
    arr_own_v2 = val;
  }
  const std::vector<rf_owner::OwnerV2> &get_vec_own_v2() const {
    return vec_own_v2;
  }
  void set_vec_own_v2(const std::vector<rf_owner::OwnerV2> &val) {
    vec_own_v2 = val;
  }
  const rf_owner::nested::OwnerV3 &get_own_v3() const { return own_v3; }
  void set_own_v3(const rf_owner::nested::OwnerV3 &val) { own_v3 = val; }
  const std::array<rf_owner::nested::OwnerV3, 10> &get_arr_own_v3() const {
    return arr_own_v3;
  }
  void set_arr_own_v3(const std::array<rf_owner::nested::OwnerV3, 10> &val) {
    arr_own_v3 = val;
  }
  const std::vector<rf_owner::nested::OwnerV3> &get_vec_own_v3() const {
    return vec_own_v3;
  }
  void set_vec_own_v3(const std::vector<rf_owner::nested::OwnerV3> &val) {
    vec_own_v3 = val;
  }
  const OwnerV4 &get_own_v4() const { return own_v4; }
  void set_own_v4(const OwnerV4 &val) { own_v4 = val; }
  const std::array<OwnerV4, 10> &get_arr_own_v4() const { return arr_own_v4; }
  void set_arr_own_v4(const std::array<OwnerV4, 10> &val) { arr_own_v4 = val; }
  const std::vector<OwnerV4> &get_vec_own_v4() const { return vec_own_v4; }
  void set_vec_own_v4(const std::vector<OwnerV4> &val) { vec_own_v4 = val; }
  const std::array<rf_owner::Owner, 10> &get_arr_own() const { return arr_own; }

  // Enum type getters/setters
  PetType get_pet_type() const { return pet_type; }
  void set_pet_type(PetType val) { pet_type = val; }
  const std::array<PetType, 2> &get_arr_pet_type() const {
    return arr_pet_type;
  }
  void set_arr_pet_type(const std::array<PetType, 2> &val) {
    arr_pet_type = val;
  }
  const std::vector<PetType> &get_vec_pet_type() const { return vec_pet_type; }
  void set_vec_pet_type(const std::vector<PetType> &val) { vec_pet_type = val; }

  // arr_u8 getter/setter
  const std::array<uint8_t, 100> &get_arr_u8() const { return arr_u8; }
  void set_arr_u8(const std::array<uint8_t, 100> &val) { arr_u8 = val; }

  // Serialization
  void dump(std::vector<uint8_t>& out) const;
  inline size_t load(const std::vector<uint8_t>& src, size_t& offset){
    this->~Pet();
    std::memcpy(this, src.data() + offset, sizeof(Pet));
    offset += sizeof(Pet);
    // 1. std::string s
    std::string s_tmp;
    rf_common::read_string(src, offset, s_tmp);
    new (&s) std::string(std::move(s_tmp));
    // 2. std::array<std::string, 2> arr_s
    for (size_t i = 0; i < arr_s.size(); ++i) {
        std::string arr_s_tmp;
        rf_common::read_string(src, offset, arr_s_tmp);
        new (&arr_s[i]) std::string(std::move(arr_s_tmp));
    }
    // 3. std::vector<double> vec_d
    uint32_t sz;
    std::memcpy(&sz, &src[offset], sizeof(sz));
    offset += sizeof(sz);
    std::vector<double> vec_d_tmp(sz);
    if (sz) {
        std::memcpy(vec_d_tmp.data(), &src[offset], sz * sizeof(vec_d_tmp[0]));
        offset += sz * sizeof(vec_d_tmp[0]);
    }
    new (&vec_d) std::vector<double>(std::move(vec_d_tmp));
    // 4. std::vector<float> vec_f
    std::memcpy(&sz, &src[offset], sizeof(sz));
    offset += sizeof(sz);
    std::vector<float> vec_f_tmp(sz);
    if (sz) {
        std::memcpy(vec_f_tmp.data(), &src[offset], sz * sizeof(vec_f_tmp[0]));
        offset += sz * sizeof(vec_f_tmp[0]);
    }
    new (&vec_f) std::vector<float>(std::move(vec_f_tmp));
    // 5. std::vector<int32_t> vec_i32
    std::memcpy(&sz, &src[offset], sizeof(sz));
    offset += sizeof(sz);
    std::vector<int32_t> vec_i32_tmp(sz);
    if (sz) {
        std::memcpy(vec_i32_tmp.data(), &src[offset], sz * sizeof(vec_i32_tmp[0]));
        offset += sz * sizeof(vec_i32_tmp[0]);
    }
    new (&vec_i32) std::vector<int32_t>(std::move(vec_i32_tmp));
    // 6. std::vector<int64_t> vec_i64
    std::memcpy(&sz, &src[offset], sizeof(sz));
    offset += sizeof(sz);
    std::vector<int64_t> vec_i64_tmp(sz);
    if (sz) {
        std::memcpy(vec_i64_tmp.data(), &src[offset], sz * sizeof(vec_i64_tmp[0]));
        offset += sz * sizeof(vec_i64_tmp[0]);
    }
    new (&vec_i64) std::vector<int64_t>(std::move(vec_i64_tmp));
    // 7. std::vector<uint32_t> vec_u32
    std::memcpy(&sz, &src[offset], sizeof(sz));
    offset += sizeof(sz);
    std::vector<uint32_t> vec_u32_tmp(sz);
    if (sz) {
        std::memcpy(vec_u32_tmp.data(), &src[offset], sz * sizeof(vec_u32_tmp[0]));
        offset += sz * sizeof(vec_u32_tmp[0]);
    }
    new (&vec_u32) std::vector<uint32_t>(std::move(vec_u32_tmp));
    // 8. std::vector<uint64_t> vec_u64
    std::memcpy(&sz, &src[offset], sizeof(sz));
    offset += sizeof(sz);
    std::vector<uint64_t> vec_u64_tmp(sz);
    if (sz) {
        std::memcpy(vec_u64_tmp.data(), &src[offset], sz * sizeof(vec_u64_tmp[0]));
        offset += sz * sizeof(vec_u64_tmp[0]);
    }
    new (&vec_u64) std::vector<uint64_t>(std::move(vec_u64_tmp));
    // 9. std::vector<bool> vec_bval
    std::memcpy(&sz, &src[offset], sizeof(sz));
    offset += sizeof(sz);
    std::vector<bool> vec_bval_tmp(sz);
    for (uint32_t i = 0; i < sz; ++i) {
        uint8_t bv;
        std::memcpy(&bv, &src[offset], sizeof(bv));
        offset += sizeof(bv);
        vec_bval_tmp[i] = (bv != 0);
    }
    new (&vec_bval) std::vector<bool>(std::move(vec_bval_tmp));
    // 10. std::vector<std::string> vec_s
    std::memcpy(&sz, &src[offset], sizeof(sz));
    offset += sizeof(sz);
    std::vector<std::string> vec_s_tmp(sz);
    for (uint32_t i = 0; i < sz; ++i) {
        std::string s_tmp;
        rf_common::read_string(src, offset, s_tmp);
        new (&vec_s_tmp[i]) std::string(std::move(s_tmp));
    }
    new (&vec_s) std::vector<std::string>(std::move(vec_s_tmp));
    // 11. rf_owner::Owner own
    {
        rf_owner::Owner tmp;
        tmp.load(src, offset);
        new (&own) rf_owner::Owner(std::move(tmp));
    }
    // 12. std::array<rf_owner::Owner, 10> arr_own
    for (size_t i = 0; i < arr_own.size(); ++i) {
        new (&arr_own[i]) rf_owner::Owner();
        rf_owner::Owner tmp;
        tmp.load(src, offset);
        arr_own[i] = std::move(tmp);
    }
    // 13. std::vector<rf_owner::Owner> vec_own
    std::memcpy(&sz, &src[offset], sizeof(sz));
    offset += sizeof(sz);
    std::vector<rf_owner::Owner> vec_own_tmp(sz);
    for (uint32_t i = 0; i < sz; ++i) {
        rf_owner::Owner tmp;
        tmp.load(src, offset);
        vec_own_tmp[i] = std::move(tmp);
    }
    new (&vec_own) std::vector<rf_owner::Owner>(std::move(vec_own_tmp));
    // 14. rf_owner::OwnerV2 own_v2
    {
        rf_owner::OwnerV2 tmp;
        tmp.load(src, offset);
        new (&own_v2) rf_owner::OwnerV2(std::move(tmp));
    }
    // 15. std::array<rf_owner::OwnerV2, 10> arr_own_v2
    for (size_t i = 0; i < arr_own_v2.size(); ++i) {
        new (&arr_own_v2[i]) rf_owner::OwnerV2();
        rf_owner::OwnerV2 tmp;
        tmp.load(src, offset);
        arr_own_v2[i] = std::move(tmp);
    }
    // 16. std::vector<rf_owner::OwnerV2> vec_own_v2
    std::memcpy(&sz, &src[offset], sizeof(sz));
    offset += sizeof(sz);
    std::vector<rf_owner::OwnerV2> vec_own_v2_tmp(sz);
    for (uint32_t i = 0; i < sz; ++i) {
        rf_owner::OwnerV2 tmp;
        tmp.load(src, offset);
        vec_own_v2_tmp[i] = std::move(tmp);
    }
    new (&vec_own_v2) std::vector<rf_owner::OwnerV2>(std::move(vec_own_v2_tmp));
    // 17. rf_owner::nested::OwnerV3 own_v3
    {
        rf_owner::nested::OwnerV3 tmp;
        tmp.load(src, offset);
        new (&own_v3) rf_owner::nested::OwnerV3(std::move(tmp));
    }
    // 18. std::array<rf_owner::nested::OwnerV3, 10> arr_own_v3
    for (size_t i = 0; i < arr_own_v3.size(); ++i) {
        new (&arr_own_v3[i]) rf_owner::nested::OwnerV3();
        rf_owner::nested::OwnerV3 tmp;
        tmp.load(src, offset);
        arr_own_v3[i] = std::move(tmp);
    }
    // 19. std::vector<rf_owner::nested::OwnerV3> vec_own_v3
    std::memcpy(&sz, &src[offset], sizeof(sz));
    offset += sizeof(sz);
    std::vector<rf_owner::nested::OwnerV3> vec_own_v3_tmp(sz);
    for (uint32_t i = 0; i < sz; ++i) {
        rf_owner::nested::OwnerV3 tmp;
        tmp.load(src, offset);
        vec_own_v3_tmp[i] = std::move(tmp);
    }
    new (&vec_own_v3) std::vector<rf_owner::nested::OwnerV3>(std::move(vec_own_v3_tmp));
    // 20. OwnerV4 own_v4
    {
        OwnerV4 tmp;
        tmp.load(src, offset);
        new (&own_v4) OwnerV4(std::move(tmp));
    }
    // 21. std::array<OwnerV4, 10> arr_own_v4
    for (size_t i = 0; i < arr_own_v4.size(); ++i) {
        new (&arr_own_v4[i]) OwnerV4();
        OwnerV4 tmp;
        tmp.load(src, offset);
        arr_own_v4[i] = std::move(tmp);
    }
    // 22. std::vector<OwnerV4> vec_own_v4
    std::memcpy(&sz, &src[offset], sizeof(sz));
    offset += sizeof(sz);
    std::vector<OwnerV4> vec_own_v4_tmp(sz);
    for (uint32_t i = 0; i < sz; ++i) {
        OwnerV4 tmp;
        tmp.load(src, offset);
        vec_own_v4_tmp[i] = std::move(tmp);
    }
    new (&vec_own_v4) std::vector<OwnerV4>(std::move(vec_own_v4_tmp));
    // 14. PetType pet_type (POD, handled by memcpy)
    // 15. std::array<PetType, 2> arr_pet_type (POD, handled by memcpy)

    // 16. std::vector<PetType> vec_pet_type
    std::memcpy(&sz, &src[offset], sizeof(sz));
    offset += sizeof(sz);
    std::vector<PetType> vec_pet_type_tmp(sz);
    if (sz) {
        std::memcpy(vec_pet_type_tmp.data(), &src[offset], sz * sizeof(vec_pet_type_tmp[0]));
        offset += sz * sizeof(vec_pet_type_tmp[0]);
    }
    new (&vec_pet_type) std::vector<PetType>(std::move(vec_pet_type_tmp));
    // 17. std::array<uint8_t, 100> arr_u8 (POD, handled by memcpy)
    return offset;
  }
  void load(const std::vector<uint8_t>& src);
};

} // namespace rf_pet