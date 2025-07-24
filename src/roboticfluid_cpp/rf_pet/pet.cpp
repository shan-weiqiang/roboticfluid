#include "roboticfluid_cpp/rf_pet/pet.hpp"
#include <cstring>
#include <new>
#include <string>

using namespace rf_owner;
using namespace rf_pet;

// Helper to write a length-prefixed string
static void write_string(std::string &out, const std::string &s) {
  uint32_t len = static_cast<uint32_t>(s.size());
  out.append(reinterpret_cast<const char *>(&len), sizeof(len));
  out.append(s.data(), len);
}

// Helper to read a length-prefixed string
static void read_string(const std::string &src, size_t &offset,
                        std::string &s) {
  uint32_t len = 0;
  std::memcpy(&len, &src[offset], sizeof(len));
  offset += sizeof(len);
  s.assign(&src[offset], len);
  offset += len;
}

std::string Pet::freeze() const {
  // 1. Block copy the entire object (shallow copy, including pointers in
  // dynamic members)
  std::string out(sizeof(Pet), '\0');
  std::memcpy(&out[0], this, sizeof(Pet));

  // 2. Serialize all dynamic members in the exact order of appearance
  // 1. std::string s
  write_string(out, s);
  // 2. std::array<std::string, 2> arr_s
  for (const auto &s_ : arr_s)
    write_string(out, s_);
  // 3. std::vector<double> vec_d
  uint32_t sz = static_cast<uint32_t>(vec_d.size());
  out.append(reinterpret_cast<const char *>(&sz), sizeof(sz));
  if (sz)
    out.append(reinterpret_cast<const char *>(vec_d.data()),
               sz * sizeof(vec_d[0]));
  // 4. std::vector<float> vec_f
  sz = static_cast<uint32_t>(vec_f.size());
  out.append(reinterpret_cast<const char *>(&sz), sizeof(sz));
  if (sz)
    out.append(reinterpret_cast<const char *>(vec_f.data()),
               sz * sizeof(vec_f[0]));
  // 5. std::vector<int32_t> vec_i32
  sz = static_cast<uint32_t>(vec_i32.size());
  out.append(reinterpret_cast<const char *>(&sz), sizeof(sz));
  if (sz)
    out.append(reinterpret_cast<const char *>(vec_i32.data()),
               sz * sizeof(vec_i32[0]));
  // 6. std::vector<int64_t> vec_i64
  sz = static_cast<uint32_t>(vec_i64.size());
  out.append(reinterpret_cast<const char *>(&sz), sizeof(sz));
  if (sz)
    out.append(reinterpret_cast<const char *>(vec_i64.data()),
               sz * sizeof(vec_i64[0]));
  // 7. std::vector<uint32_t> vec_u32
  sz = static_cast<uint32_t>(vec_u32.size());
  out.append(reinterpret_cast<const char *>(&sz), sizeof(sz));
  if (sz)
    out.append(reinterpret_cast<const char *>(vec_u32.data()),
               sz * sizeof(vec_u32[0]));
  // 8. std::vector<uint64_t> vec_u64
  sz = static_cast<uint32_t>(vec_u64.size());
  out.append(reinterpret_cast<const char *>(&sz), sizeof(sz));
  if (sz)
    out.append(reinterpret_cast<const char *>(vec_u64.data()),
               sz * sizeof(vec_u64[0]));
  // 9. std::vector<bool> vec_bval
  sz = static_cast<uint32_t>(vec_bval.size());
  out.append(reinterpret_cast<const char *>(&sz), sizeof(sz));
  for (auto b : vec_bval) {
    uint8_t bv = b ? 1 : 0;
    out.append(reinterpret_cast<const char *>(&bv), sizeof(bv));
  }
  // 10. std::vector<std::string> vec_s
  sz = static_cast<uint32_t>(vec_s.size());
  out.append(reinterpret_cast<const char *>(&sz), sizeof(sz));
  for (const auto &s_ : vec_s)
    write_string(out, s_);
  // 11. rf_owner::Owner own
  out.append(own.freeze());
  // 12. std::array<rf_owner::Owner, 10> arr_own
  for (const auto &o : arr_own)
    out.append(o.freeze());
  // 13. std::vector<rf_owner::Owner> vec_own
  sz = static_cast<uint32_t>(vec_own.size());
  out.append(reinterpret_cast<const char *>(&sz), sizeof(sz));
  for (const auto &o : vec_own)
    out.append(o.freeze());
  // 14. PetType pet_type (POD, handled by block copy)
  // 15. std::array<PetType, 2> arr_pet_type (POD, handled by block copy)
  // 16. std::vector<PetType> vec_pet_type
  sz = static_cast<uint32_t>(vec_pet_type.size());
  out.append(reinterpret_cast<const char *>(&sz), sizeof(sz));
  if (sz)
    out.append(reinterpret_cast<const char *>(vec_pet_type.data()),
               sz * sizeof(vec_pet_type[0]));
  // 17. std::array<uint8_t, 100> arr_u8 (POD, handled by block copy)
  return out;
}

// WARN: always use placement new after calling destructor manually
void Pet::melt(const std::string &src) {
  this->~Pet();
  std::memcpy(this, src.data(), sizeof(Pet));
  size_t offset = sizeof(Pet);

  // 1. std::string s
  std::string s_tmp;
  read_string(src, offset, s_tmp);
  new (&s) std::string(std::move(s_tmp));

  // 2. std::array<std::string, 2> arr_s
  for (size_t i = 0; i < arr_s.size(); ++i) {
    std::string arr_s_tmp;
    read_string(src, offset, arr_s_tmp);
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
    read_string(src, offset, s_tmp);
    new (&vec_s_tmp[i]) std::string(std::move(s_tmp));
  }
  new (&vec_s) std::vector<std::string>(std::move(vec_s_tmp));

  // 11. rf_owner::Owner own
  {
    size_t owner_start = offset;
    rf_owner::Owner tmp;
    size_t consumed = tmp.melt(
        std::string(src.data() + owner_start, src.size() - owner_start));
    new (&own) rf_owner::Owner(
        std::move(tmp)); // placement new for deserialized object
    offset += consumed;
  }

  // 12. std::array<rf_owner::Owner, 10> arr_own
  for (size_t i = 0; i < arr_own.size(); ++i) {
    new (&arr_own[i]) rf_owner::Owner(); // placement new, in case melt is
                                         // called multiple times
    size_t owner_start = offset;
    rf_owner::Owner tmp;
    size_t consumed = tmp.melt(
        std::string(src.data() + owner_start, src.size() - owner_start));
    arr_own[i] = std::move(tmp);
    offset += consumed;
  }

  // 13. std::vector<rf_owner::Owner> vec_own
  std::memcpy(&sz, &src[offset], sizeof(sz));
  offset += sizeof(sz);
  std::vector<rf_owner::Owner> vec_own_tmp(sz);
  for (uint32_t i = 0; i < sz; ++i) {
    size_t owner_start = offset;
    rf_owner::Owner tmp;
    size_t consumed = tmp.melt(
        std::string(src.data() + owner_start, src.size() - owner_start));
    vec_own_tmp[i] = std::move(tmp);
    offset += consumed;
  }
  new (&vec_own) std::vector<rf_owner::Owner>(std::move(vec_own_tmp));

  // 14. PetType pet_type (POD, handled by memcpy)
  // 15. std::array<PetType, 2> arr_pet_type (POD, handled by memcpy)

  // 16. std::vector<PetType> vec_pet_type
  std::memcpy(&sz, &src[offset], sizeof(sz));
  offset += sizeof(sz);
  std::vector<PetType> vec_pet_type_tmp(sz);
  if (sz) {
    std::memcpy(vec_pet_type_tmp.data(), &src[offset],
                sz * sizeof(vec_pet_type_tmp[0]));
    offset += sz * sizeof(vec_pet_type_tmp[0]);
  }
  new (&vec_pet_type) std::vector<PetType>(std::move(vec_pet_type_tmp));

  // 17. std::array<uint8_t, 100> arr_u8 (POD, handled by memcpy)
}