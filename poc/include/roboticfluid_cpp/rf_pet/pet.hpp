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
  // Arrays for each basic type (size 10000)
  std::array<double, 10000> arr_d;
  std::array<float, 10000> arr_f;
  std::array<int32_t, 10000> arr_i32;
  std::array<int64_t, 10000> arr_i64;
  std::array<uint32_t, 10000> arr_u32;
  std::array<uint64_t, 10000> arr_u64;
  std::array<bool, 10000> arr_bval;
  std::array<std::string, 10000> arr_s;
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
  std::array<rf_owner::Owner, 10000> arr_own;
  std::vector<rf_owner::Owner> vec_own;
  // OwnerV2
  rf_owner::OwnerV2 own_v2;
  std::array<rf_owner::OwnerV2, 10000> arr_own_v2;
  std::vector<rf_owner::OwnerV2> vec_own_v2;
  // OwnerV3
  rf_owner::nested::OwnerV3 own_v3;
  std::array<rf_owner::nested::OwnerV3, 10000> arr_own_v3;
  std::vector<rf_owner::nested::OwnerV3> vec_own_v3;
  // OwnerV4
  OwnerV4 own_v4;
  std::array<OwnerV4, 10000> arr_own_v4;
  std::vector<OwnerV4> vec_own_v4;

  // Enum types
  PetType pet_type;
  // Arrays for enum
  std::array<PetType, 10000> arr_pet_type;
  // Vector for enum
  std::vector<PetType> vec_pet_type;

  // New member: array of uint8_t
  std::array<uint8_t, 10000> arr_u8;

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
  const std::array<double, 10000> &get_arr_d() const { return arr_d; }
  void set_arr_d(const std::array<double, 10000> &val) { arr_d = val; }
  const std::array<float, 10000> &get_arr_f() const { return arr_f; }
  void set_arr_f(const std::array<float, 10000> &val) { arr_f = val; }
  const std::array<int32_t, 10000> &get_arr_i32() const { return arr_i32; }
  void set_arr_i32(const std::array<int32_t, 10000> &val) { arr_i32 = val; }
  const std::array<int64_t, 10000> &get_arr_i64() const { return arr_i64; }
  void set_arr_i64(const std::array<int64_t, 10000> &val) { arr_i64 = val; }
  const std::array<uint32_t, 10000> &get_arr_u32() const { return arr_u32; }
  void set_arr_u32(const std::array<uint32_t, 10000> &val) { arr_u32 = val; }
  const std::array<uint64_t, 10000> &get_arr_u64() const { return arr_u64; }
  void set_arr_u64(const std::array<uint64_t, 10000> &val) { arr_u64 = val; }
  const std::array<bool, 10000> &get_arr_bval() const { return arr_bval; }
  void set_arr_bval(const std::array<bool, 10000> &val) { arr_bval = val; }
  const std::array<std::string, 10000> &get_arr_s() const { return arr_s; }
  void set_arr_s(const std::array<std::string, 10000> &val) { arr_s = val; }
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
  void set_arr_own(const std::array<rf_owner::Owner, 10000> &val) {
    arr_own = val;
  }
  const std::vector<rf_owner::Owner> &get_vec_own() const { return vec_own; }
  void set_vec_own(const std::vector<rf_owner::Owner> &val) { vec_own = val; }
  const rf_owner::OwnerV2 &get_own_v2() const { return own_v2; }
  void set_own_v2(const rf_owner::OwnerV2 &val) { own_v2 = val; }
  const std::array<rf_owner::OwnerV2, 10000> &get_arr_own_v2() const {
    return arr_own_v2;
  }
  void set_arr_own_v2(const std::array<rf_owner::OwnerV2, 10000> &val) {
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
  const std::array<rf_owner::nested::OwnerV3, 10000> &get_arr_own_v3() const {
    return arr_own_v3;
  }
  void set_arr_own_v3(const std::array<rf_owner::nested::OwnerV3, 10000> &val) {
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
  const std::array<OwnerV4, 10000> &get_arr_own_v4() const { return arr_own_v4; }
  void set_arr_own_v4(const std::array<OwnerV4, 10000> &val) { arr_own_v4 = val; }
  const std::vector<OwnerV4> &get_vec_own_v4() const { return vec_own_v4; }
  void set_vec_own_v4(const std::vector<OwnerV4> &val) { vec_own_v4 = val; }
  const std::array<rf_owner::Owner, 10000> &get_arr_own() const { return arr_own; }

  // Enum type getters/setters
  PetType get_pet_type() const { return pet_type; }
  void set_pet_type(PetType val) { pet_type = val; }
  const std::array<PetType, 10000> &get_arr_pet_type() const {
    return arr_pet_type;
  }
  void set_arr_pet_type(const std::array<PetType, 10000> &val) {
    arr_pet_type = val;
  }
  const std::vector<PetType> &get_vec_pet_type() const { return vec_pet_type; }
  void set_vec_pet_type(const std::vector<PetType> &val) { vec_pet_type = val; }

  // arr_u8 getter/setter
  const std::array<uint8_t, 10000> &get_arr_u8() const { return arr_u8; }
  void set_arr_u8(const std::array<uint8_t, 10000> &val) { arr_u8 = val; }

  // Serialization
  void dump(std::vector<uint8_t>& out) const;
  
  // Compressed serialization methods
  void dump_compressed(std::vector<uint8_t>& out) const {
    std::vector<uint8_t> serialized;
    dump(serialized);
    std::vector<uint8_t> compressed = rf_common::compress_lz4(serialized);
    
    // Prepend the original size to the compressed data
    rf_common::write_varint(out, static_cast<uint32_t>(serialized.size()));
    out.insert(out.end(), compressed.begin(), compressed.end());
  }
  
  bool load_compressed(const std::vector<uint8_t>& compressed_data) {
    if (compressed_data.empty()) {
      return false;
    }
    
    // Extract the original size from the beginning
    size_t offset = 0;
    uint32_t original_size;
    rf_common::read_varint(compressed_data, offset, original_size);
    
    // Extract the actual compressed data
    std::vector<uint8_t> actual_compressed_data(
        compressed_data.begin() + offset, 
        compressed_data.end()
    );
    
    // Decompress
    std::vector<uint8_t> decompressed = rf_common::decompress_lz4(actual_compressed_data, original_size);
    if (decompressed.empty()) {
      return false;
    }
    
    try {
      load(decompressed);
      return true;
    } catch (...) {
      return false;
    }
  }
  
  // Internal method for array serialization - only dumps dynamic parts
  inline void dump_dynamic_only(std::vector<uint8_t>& out) const {
    // Only serialize the dynamic parts (std::string and std::vector members)
    // POD parts are handled by memcpy in the main dump method
    
    // 1. std::string s
    rf_common::write_string_optimized(out, s);
    // 2. std::array<std::string, 10000> arr_s
    for (const auto &s_ : arr_s)
        rf_common::write_string_optimized(out, s_);
    // 3. std::vector<double> vec_d
    rf_common::write_vector_optimized(out, vec_d);
    // 4. std::vector<float> vec_f
    rf_common::write_vector_optimized(out, vec_f);
    // 5. std::vector<int32_t> vec_i32
    rf_common::write_vector_optimized(out, vec_i32);
    // 6. std::vector<int64_t> vec_i64
    rf_common::write_vector_optimized(out, vec_i64);
    // 7. std::vector<uint32_t> vec_u32
    rf_common::write_vector_optimized(out, vec_u32);
    // 8. std::vector<uint64_t> vec_u64
    rf_common::write_vector_optimized(out, vec_u64);
    // 9. std::vector<bool> vec_bval - special case for bool
    rf_common::write_varint(out, static_cast<uint32_t>(vec_bval.size()));
    for (auto b : vec_bval) {
        uint8_t bv = b ? 1 : 0;
        out.push_back(bv);
    }
    // 10. std::vector<std::string> vec_s
    rf_common::write_varint(out, static_cast<uint32_t>(vec_s.size()));
    for (const auto &s_ : vec_s)
        rf_common::write_string_optimized(out, s_);
    // 11. rf_owner::Owner own
    own.dump(out);
    // 12. std::array<rf_owner::Owner, 10000> arr_own
    for (const auto &o : arr_own)
        o.dump_dynamic_only(out);
    // 13. std::vector<rf_owner::Owner> vec_own
    rf_common::write_varint(out, static_cast<uint32_t>(vec_own.size()));
    for (const auto &o : vec_own)
        o.dump(out);
    // 14. rf_owner::OwnerV2 own_v2
    own_v2.dump(out);
    // 15. std::array<rf_owner::OwnerV2, 10000> arr_own_v2
    for (const auto &o : arr_own_v2)
        o.dump_dynamic_only(out);
    // 16. std::vector<rf_owner::OwnerV2> vec_own_v2
    rf_common::write_varint(out, static_cast<uint32_t>(vec_own_v2.size()));
    for (const auto &o : vec_own_v2)
        o.dump(out);
    // 17. rf_owner::nested::OwnerV3 own_v3
    own_v3.dump(out);
    // 18. std::array<rf_owner::nested::OwnerV3, 10000> arr_own_v3
    for (const auto &o : arr_own_v3)
        o.dump_dynamic_only(out);
    // 19. std::vector<rf_owner::nested::OwnerV3> vec_own_v3
    rf_common::write_varint(out, static_cast<uint32_t>(vec_own_v3.size()));
    for (const auto &o : vec_own_v3)
        o.dump(out);
    // 20. OwnerV4 own_v4
    own_v4.dump(out);
    // 21. std::array<OwnerV4, 10000> arr_own_v4
    for (const auto &o : arr_own_v4)
        o.dump_dynamic_only(out);
    // 22. std::vector<OwnerV4> vec_own_v4
    rf_common::write_varint(out, static_cast<uint32_t>(vec_own_v4.size()));
    for (const auto &o : vec_own_v4)
        o.dump(out);
    // 23. std::vector<PetType> vec_pet_type
    rf_common::write_vector_optimized(out, vec_pet_type);
  }
  // Internal method for array deserialization - only loads dynamic parts
  inline size_t load_dynamic_only(const std::vector<uint8_t>& src, size_t& offset) {
    // Only load the dynamic parts
    // The POD parts are already loaded via memcpy
    
    // 1. std::string s
    std::string s_tmp;
    rf_common::read_string_optimized(src, offset, s_tmp);
    new (&s) std::string(std::move(s_tmp));
    // 2. std::array<std::string, 10000> arr_s
    for (size_t i = 0; i < arr_s.size(); ++i) {
        std::string arr_s_tmp;
        rf_common::read_string_optimized(src, offset, arr_s_tmp);
        new (&arr_s[i]) std::string(std::move(arr_s_tmp));
    }
    // 3. std::vector<double> vec_d
    std::vector<double> vec_d_tmp;
    rf_common::read_vector_optimized(src, offset, vec_d_tmp);
    new (&vec_d) std::vector<double>(std::move(vec_d_tmp));
    // 4. std::vector<float> vec_f
    std::vector<float> vec_f_tmp;
    rf_common::read_vector_optimized(src, offset, vec_f_tmp);
    new (&vec_f) std::vector<float>(std::move(vec_f_tmp));
    // 5. std::vector<int32_t> vec_i32
    std::vector<int32_t> vec_i32_tmp;
    rf_common::read_vector_optimized(src, offset, vec_i32_tmp);
    new (&vec_i32) std::vector<int32_t>(std::move(vec_i32_tmp));
    // 6. std::vector<int64_t> vec_i64
    std::vector<int64_t> vec_i64_tmp;
    rf_common::read_vector_optimized(src, offset, vec_i64_tmp);
    new (&vec_i64) std::vector<int64_t>(std::move(vec_i64_tmp));
    // 7. std::vector<uint32_t> vec_u32
    std::vector<uint32_t> vec_u32_tmp;
    rf_common::read_vector_optimized(src, offset, vec_u32_tmp);
    new (&vec_u32) std::vector<uint32_t>(std::move(vec_u32_tmp));
    // 8. std::vector<uint64_t> vec_u64
    std::vector<uint64_t> vec_u64_tmp;
    rf_common::read_vector_optimized(src, offset, vec_u64_tmp);
    new (&vec_u64) std::vector<uint64_t>(std::move(vec_u64_tmp));
    // 9. std::vector<bool> vec_bval
    uint32_t sz;
    rf_common::read_varint(src, offset, sz);
    std::vector<bool> vec_bval_tmp(sz);
    for (uint32_t i = 0; i < sz; ++i) {
        uint8_t bv;
        std::memcpy(&bv, &src[offset], sizeof(bv));
        offset += sizeof(bv);
        vec_bval_tmp[i] = (bv != 0);
    }
    new (&vec_bval) std::vector<bool>(std::move(vec_bval_tmp));
    // 10. std::vector<std::string> vec_s
    rf_common::read_varint(src, offset, sz);
    std::vector<std::string> vec_s_tmp(sz);
    for (uint32_t i = 0; i < sz; ++i) {
        std::string s_tmp;
        rf_common::read_string_optimized(src, offset, s_tmp);
        vec_s_tmp[i] = std::move(s_tmp);
    }
    new (&vec_s) std::vector<std::string>(std::move(vec_s_tmp));
    // 11. rf_owner::Owner own
    {
        rf_owner::Owner tmp;
        tmp.load(src, offset);
        new (&own) rf_owner::Owner(std::move(tmp));
    }
    // 12. std::array<rf_owner::Owner, 10000> arr_own
    for (size_t i = 0; i < arr_own.size(); ++i) {
        // Use load_dynamic_only since POD parts are already loaded via memcpy
        // Don't call default constructor as it would zero out the POD content
        arr_own[i].load_dynamic_only(src, offset);
    }
    // 13. std::vector<rf_owner::Owner> vec_own
    rf_common::read_varint(src, offset, sz);
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
    // 15. std::array<rf_owner::OwnerV2, 10000> arr_own_v2
    for (size_t i = 0; i < arr_own_v2.size(); ++i) {
        // Use load_dynamic_only since POD parts are already loaded via memcpy
        // Don't call default constructor as it would zero out the POD content
        arr_own_v2[i].load_dynamic_only(src, offset);
    }
    // 16. std::vector<rf_owner::OwnerV2> vec_own_v2
    rf_common::read_varint(src, offset, sz);
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
    // 18. std::array<rf_owner::nested::OwnerV3, 10000> arr_own_v3
    for (size_t i = 0; i < arr_own_v3.size(); ++i) {
        // Use load_dynamic_only since POD parts are already loaded via memcpy
        // Don't call default constructor as it would zero out the POD content
        arr_own_v3[i].load_dynamic_only(src, offset);
    }
    // 19. std::vector<rf_owner::nested::OwnerV3> vec_own_v3
    rf_common::read_varint(src, offset, sz);
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
    // 21. std::array<OwnerV4, 10000> arr_own_v4
    for (size_t i = 0; i < arr_own_v4.size(); ++i) {
        // Use load_dynamic_only since POD parts are already loaded via memcpy
        // Don't call default constructor as it would zero out the POD content
        arr_own_v4[i].load_dynamic_only(src, offset);
    }
    // 22. std::vector<OwnerV4> vec_own_v4
    rf_common::read_varint(src, offset, sz);
    std::vector<OwnerV4> vec_own_v4_tmp(sz);
    for (uint32_t i = 0; i < sz; ++i) {
        OwnerV4 tmp;
        tmp.load(src, offset);
        vec_own_v4_tmp[i] = std::move(tmp);
    }
    new (&vec_own_v4) std::vector<OwnerV4>(std::move(vec_own_v4_tmp));
    // 23. std::vector<PetType> vec_pet_type
    std::vector<PetType> vec_pet_type_tmp;
    rf_common::read_vector_optimized(src, offset, vec_pet_type_tmp);
    new (&vec_pet_type) std::vector<PetType>(std::move(vec_pet_type_tmp));
    return offset;
  }
  inline size_t load(const std::vector<uint8_t>& src, size_t& offset){
    this->~Pet();
    std::memcpy(this, src.data() + offset, sizeof(Pet));
    offset += sizeof(Pet);
    // Call load_dynamic_only to handle all dynamic members
    return load_dynamic_only(src, offset);
  }
  void load(const std::vector<uint8_t>& src);
};

} // namespace rf_pet