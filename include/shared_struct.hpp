#pragma once
#include <array>
#include <vector>
#include <string>
#include <cstdint>
#include <stdexcept>

struct CustomType {
    int32_t a;
    double b;

    int32_t get_a() const { return a; }
    void set_a(int32_t val) { a = val; }
    double get_b() const { return b; }
    void set_b(double val) { b = val; }
};

struct SharedStruct {
    // Basic types
    double d;
    float f;
    int32_t i32;
    int64_t i64;
    uint32_t u32;
    uint64_t u64;
    bool bval;
    std::string s;

    // std::array for each basic type
    std::array<double, 4> arr_d;
    std::array<float, 4> arr_f;
    std::array<int32_t, 4> arr_i32;
    std::array<int64_t, 4> arr_i64;
    std::array<uint32_t, 4> arr_u32;
    std::array<uint64_t, 4> arr_u64;
    std::array<bool, 4> arr_bval;
    std::array<std::string, 4> arr_s;

    // std::vector for each basic type
    std::vector<double> vec_d;
    std::vector<float> vec_f;
    std::vector<int32_t> vec_i32;
    std::vector<int64_t> vec_i64;
    std::vector<uint32_t> vec_u32;
    std::vector<uint64_t> vec_u64;
    std::vector<bool> vec_bval;
    std::vector<std::string> vec_s;

    // std::array and std::vector for custom type
    std::array<CustomType, 2> arr_custom;
    std::vector<CustomType> vec_custom;

    // Getters and setters for each field
    // Basic types
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
    std::string get_s() const { return s; }
    void set_s(const std::string& val) { s = val; }

    // Arrays: get/set by index, get whole array
#define ARRAY_GETTER_SETTER(TYPE, NAME) \
    TYPE get_##NAME(size_t idx) const { return NAME.at(idx); } \
    void set_##NAME(size_t idx, TYPE val) { NAME.at(idx) = val; } \
    const std::array<TYPE, 4>& get_##NAME##_array() const { return NAME; } \
    void set_##NAME##_array(const std::array<TYPE, 4>& arr) { NAME = arr; }

    ARRAY_GETTER_SETTER(double, arr_d)
    ARRAY_GETTER_SETTER(float, arr_f)
    ARRAY_GETTER_SETTER(int32_t, arr_i32)
    ARRAY_GETTER_SETTER(int64_t, arr_i64)
    ARRAY_GETTER_SETTER(uint32_t, arr_u32)
    ARRAY_GETTER_SETTER(uint64_t, arr_u64)
    ARRAY_GETTER_SETTER(bool, arr_bval)
#undef ARRAY_GETTER_SETTER

    std::string get_arr_s(size_t idx) const { return arr_s.at(idx); }
    void set_arr_s(size_t idx, const std::string& val) { arr_s.at(idx) = val; }
    const std::array<std::string, 4>& get_arr_s_array() const { return arr_s; }
    void set_arr_s_array(const std::array<std::string, 4>& arr) { arr_s = arr; }

    // Vectors: get/set by index, get/set whole vector, resize
#define VECTOR_GETTER_SETTER(TYPE, NAME) \
    TYPE get_##NAME(size_t idx) const { return NAME.at(idx); } \
    void set_##NAME(size_t idx, TYPE val) { NAME.at(idx) = val; } \
    const std::vector<TYPE>& get_##NAME##_vector() const { return NAME; } \
    void set_##NAME##_vector(const std::vector<TYPE>& vec) { NAME = vec; } \
    void resize_##NAME(size_t n) { NAME.resize(n); }

    VECTOR_GETTER_SETTER(double, vec_d)
    VECTOR_GETTER_SETTER(float, vec_f)
    VECTOR_GETTER_SETTER(int32_t, vec_i32)
    VECTOR_GETTER_SETTER(int64_t, vec_i64)
    VECTOR_GETTER_SETTER(uint32_t, vec_u32)
    VECTOR_GETTER_SETTER(uint64_t, vec_u64)
    VECTOR_GETTER_SETTER(bool, vec_bval)
#undef VECTOR_GETTER_SETTER

    std::string get_vec_s(size_t idx) const { return vec_s.at(idx); }
    void set_vec_s(size_t idx, const std::string& val) { vec_s.at(idx) = val; }
    const std::vector<std::string>& get_vec_s_vector() const { return vec_s; }
    void set_vec_s_vector(const std::vector<std::string>& vec) { vec_s = vec; }
    void resize_vec_s(size_t n) { vec_s.resize(n); }

    // CustomType arrays and vectors
    CustomType get_arr_custom(size_t idx) const { return arr_custom.at(idx); }
    void set_arr_custom(size_t idx, const CustomType& val) { arr_custom.at(idx) = val; }
    const std::array<CustomType, 2>& get_arr_custom_array() const { return arr_custom; }
    void set_arr_custom_array(const std::array<CustomType, 2>& arr) { arr_custom = arr; }

    CustomType get_vec_custom(size_t idx) const { return vec_custom.at(idx); }
    void set_vec_custom(size_t idx, const CustomType& val) { vec_custom.at(idx) = val; }
    const std::vector<CustomType>& get_vec_custom_vector() const { return vec_custom; }
    void set_vec_custom_vector(const std::vector<CustomType>& vec) { vec_custom = vec; }
    void resize_vec_custom(size_t n) { vec_custom.resize(n); }
}; 