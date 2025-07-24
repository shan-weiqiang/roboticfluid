#pragma once

#include <array>
#include <iostream>
#include <string>
#include <vector>
#include "../rf_owner/owner.hpp"

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
  rf_owner::Owner own;
  // Arrays for custom
  std::array<rf_owner::Owner, 10> arr_own;
  // Vector for custom
  std::vector<rf_owner::Owner> vec_own;

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
  const std::array<rf_owner::Owner, 10> &get_arr_own() const { return arr_own; }
  void set_arr_own(const std::array<rf_owner::Owner, 10> &val) {
    arr_own = val;
  }
  const std::vector<rf_owner::Owner> &get_vec_own() const { return vec_own; }
  void set_vec_own(const std::vector<rf_owner::Owner> &val) { vec_own = val; }

  // Serialization
  std::string freeze() const;        // Serialize and return string
  void melt(const std::string &src); // Deserialize from src
};

} // namespace rf_pet 