#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <random>
#define ANKERL_NANOBENCH_IMPLEMENT
#include "nanobench.h"

// Protobuf
#include "pet.pb.h"
// FastDDS
#include "pet.h"
#include <fastcdr/Cdr.h>
#include <fastcdr/FastBuffer.h>
// Our own implementation
#include "../include/roboticfluid_cpp/rf_pet/pet.hpp"

// Helper to fill random string
std::string random_string(size_t length) {
    static const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    static std::mt19937 rng{std::random_device{}()};
    static std::uniform_int_distribution<> dist(0, sizeof(charset) - 2);
    std::string str(length, 0);
    for (size_t i = 0; i < length; ++i) str[i] = charset[dist(rng)];
    return str;
}

// Helper to fill Pet with specific data size
struct PetDataConfig {
    size_t vec_size;
    size_t str_len;
};

// Fill all Pet types with identical data
void fill_pet(rf_pet::Pet& pet, benchmark::pb::Pet& pb_pet, benchmark::idl::Pet& idl_pet, const PetDataConfig& cfg) {
    // Scalars
    double d = 3.14;
    float f = 2.71f;
    int32_t i32 = 42;
    int64_t i64 = 1234567890123;
    uint32_t u32 = 123456;
    uint64_t u64 = 9876543210ULL;
    bool bval = true;
    std::string s = random_string(cfg.str_len);
    std::array<double, 2> arr_d = {1.1, 2.2};
    std::array<float, 2> arr_f = {3.3f, 4.4f};
    std::array<int32_t, 2> arr_i32 = {5, 6};
    std::array<int64_t, 2> arr_i64 = {7, 8};
    std::array<uint32_t, 2> arr_u32 = {9, 10};
    std::array<uint64_t, 2> arr_u64 = {11, 12};
    std::array<bool, 2> arr_bval = {true, false};
    std::array<std::string, 2> arr_s = {random_string(cfg.str_len), random_string(cfg.str_len)};
    std::vector<double> vec_d(cfg.vec_size, 1.23);
    std::vector<float> vec_f(cfg.vec_size, 2.34f);
    std::vector<int32_t> vec_i32(cfg.vec_size, 123);
    std::vector<int64_t> vec_i64(cfg.vec_size, 456789);
    std::vector<uint32_t> vec_u32(cfg.vec_size, 987);
    std::vector<uint64_t> vec_u64(cfg.vec_size, 654321);
    std::vector<bool> vec_bval(cfg.vec_size, true);
    std::vector<std::string> vec_s(cfg.vec_size, random_string(cfg.str_len));
    std::array<uint8_t, 100> arr_u8; arr_u8.fill(0xAB);
    // Owners
    rf_owner::Owner own; own.name = "owner"; own.age = 30;
    std::array<rf_owner::Owner, 10> arr_own; for (auto& o : arr_own) { o.name = "owner"; o.age = 30; }
    std::vector<rf_owner::Owner> vec_own(cfg.vec_size, own);
    rf_owner::OwnerV2 own_v2; own_v2.name = "ownerv2"; own_v2.age = 31;
    std::array<rf_owner::OwnerV2, 10> arr_own_v2; for (auto& o : arr_own_v2) { o.name = "ownerv2"; o.age = 31; }
    std::vector<rf_owner::OwnerV2> vec_own_v2(cfg.vec_size, own_v2);
    rf_owner::nested::OwnerV3 own_v3; own_v3.name = "ownerv3"; own_v3.age = 32;
    std::array<rf_owner::nested::OwnerV3, 10> arr_own_v3; for (auto& o : arr_own_v3) { o.name = "ownerv3"; o.age = 32; }
    std::vector<rf_owner::nested::OwnerV3> vec_own_v3(cfg.vec_size, own_v3);
    OwnerV4 own_v4; own_v4.name = "ownerv4"; own_v4.age = 33;
    std::array<OwnerV4, 10> arr_own_v4; for (auto& o : arr_own_v4) { o.name = "ownerv4"; o.age = 33; }
    std::vector<OwnerV4> vec_own_v4(cfg.vec_size, own_v4);
    // Enums
    rf_pet::PetType pet_type = rf_pet::PetType::DOG;
    std::array<rf_pet::PetType, 2> arr_pet_type = {rf_pet::PetType::CAT, rf_pet::PetType::BIRD};
    std::vector<rf_pet::PetType> vec_pet_type(cfg.vec_size, rf_pet::PetType::FISH);

    // Fill custom Pet
    pet.d = d; pet.f = f; pet.i32 = i32; pet.i64 = i64; pet.u32 = u32; pet.u64 = u64; pet.bval = bval; pet.s = s;
    pet.arr_d = arr_d; pet.arr_f = arr_f; pet.arr_i32 = arr_i32; pet.arr_i64 = arr_i64; pet.arr_u32 = arr_u32; pet.arr_u64 = arr_u64; pet.arr_bval = arr_bval; pet.arr_s = arr_s;
    pet.vec_d = vec_d; pet.vec_f = vec_f; pet.vec_i32 = vec_i32; pet.vec_i64 = vec_i64; pet.vec_u32 = vec_u32; pet.vec_u64 = vec_u64; pet.vec_bval = vec_bval; pet.vec_s = vec_s;
    pet.arr_u8 = arr_u8;
    pet.own = own; pet.arr_own = arr_own; pet.vec_own = vec_own;
    pet.own_v2 = own_v2; pet.arr_own_v2 = arr_own_v2; pet.vec_own_v2 = vec_own_v2;
    pet.own_v3 = own_v3; pet.arr_own_v3 = arr_own_v3; pet.vec_own_v3 = vec_own_v3;
    pet.own_v4 = own_v4; pet.arr_own_v4 = arr_own_v4; pet.vec_own_v4 = vec_own_v4;
    pet.pet_type = pet_type; pet.arr_pet_type = arr_pet_type; pet.vec_pet_type = vec_pet_type;

    // Fill protobuf Pet
    pb_pet.set_d(d); pb_pet.set_f(f); pb_pet.set_i32(i32); pb_pet.set_i64(i64); pb_pet.set_u32(u32); pb_pet.set_u64(u64); pb_pet.set_bval(bval); pb_pet.set_s(s);
    // Fixed-size arrays (always assign exactly N elements)
    pb_pet.clear_arr_d(); for (size_t i = 0; i < arr_d.size(); ++i) pb_pet.add_arr_d(arr_d[i]); // size 2
    pb_pet.clear_arr_f(); for (size_t i = 0; i < arr_f.size(); ++i) pb_pet.add_arr_f(arr_f[i]); // size 2
    pb_pet.clear_arr_i32(); for (size_t i = 0; i < arr_i32.size(); ++i) pb_pet.add_arr_i32(arr_i32[i]); // size 2
    pb_pet.clear_arr_i64(); for (size_t i = 0; i < arr_i64.size(); ++i) pb_pet.add_arr_i64(arr_i64[i]); // size 2
    pb_pet.clear_arr_u32(); for (size_t i = 0; i < arr_u32.size(); ++i) pb_pet.add_arr_u32(arr_u32[i]); // size 2
    pb_pet.clear_arr_u64(); for (size_t i = 0; i < arr_u64.size(); ++i) pb_pet.add_arr_u64(arr_u64[i]); // size 2
    pb_pet.clear_arr_bval(); for (size_t i = 0; i < arr_bval.size(); ++i) pb_pet.add_arr_bval(arr_bval[i]); // size 2
    pb_pet.clear_arr_s(); for (size_t i = 0; i < arr_s.size(); ++i) pb_pet.add_arr_s(arr_s[i]); // size 2
    // Dynamic containers (size = cfg.vec_size)
    pb_pet.clear_vec_d(); for (auto v : vec_d) pb_pet.add_vec_d(v);
    pb_pet.clear_vec_f(); for (auto v : vec_f) pb_pet.add_vec_f(v);
    pb_pet.clear_vec_i32(); for (auto v : vec_i32) pb_pet.add_vec_i32(v);
    pb_pet.clear_vec_i64(); for (auto v : vec_i64) pb_pet.add_vec_i64(v);
    pb_pet.clear_vec_u32(); for (auto v : vec_u32) pb_pet.add_vec_u32(v);
    pb_pet.clear_vec_u64(); for (auto v : vec_u64) pb_pet.add_vec_u64(v);
    pb_pet.clear_vec_bval(); for (auto v : vec_bval) pb_pet.add_vec_bval(v);
    pb_pet.clear_vec_s(); for (auto& v : vec_s) pb_pet.add_vec_s(v);
    // arr_u8 (fixed size 100)
    pb_pet.set_arr_u8(std::string(arr_u8.begin(), arr_u8.end())); // always 100 bytes
    // Owners (fixed size 10 for arr_own, arr_own_v2, arr_own_v3, arr_own_v4)
    auto* own_pb = pb_pet.mutable_own(); own_pb->set_name(own.name); own_pb->set_age(own.age);
    pb_pet.clear_arr_own(); for (size_t i = 0; i < arr_own.size(); ++i) { auto* a = pb_pet.add_arr_own(); a->set_name(arr_own[i].name); a->set_age(arr_own[i].age); } // size 10
    pb_pet.clear_vec_own(); for (auto& o : vec_own) { auto* v = pb_pet.add_vec_own(); v->set_name(o.name); v->set_age(o.age); }
    auto* own_v2_pb = pb_pet.mutable_own_v2(); own_v2_pb->set_name(own_v2.name); own_v2_pb->set_age(own_v2.age);
    pb_pet.clear_arr_own_v2(); for (size_t i = 0; i < arr_own_v2.size(); ++i) { auto* a = pb_pet.add_arr_own_v2(); a->set_name(arr_own_v2[i].name); a->set_age(arr_own_v2[i].age); } // size 10
    pb_pet.clear_vec_own_v2(); for (auto& o : vec_own_v2) { auto* v = pb_pet.add_vec_own_v2(); v->set_name(o.name); v->set_age(o.age); }
    auto* own_v3_pb = pb_pet.mutable_own_v3(); own_v3_pb->set_name(own_v3.name); own_v3_pb->set_age(own_v3.age);
    pb_pet.clear_arr_own_v3(); for (size_t i = 0; i < arr_own_v3.size(); ++i) { auto* a = pb_pet.add_arr_own_v3(); a->set_name(arr_own_v3[i].name); a->set_age(arr_own_v3[i].age); } // size 10
    pb_pet.clear_vec_own_v3(); for (auto& o : vec_own_v3) { auto* v = pb_pet.add_vec_own_v3(); v->set_name(o.name); v->set_age(o.age); }
    auto* own_v4_pb = pb_pet.mutable_own_v4(); own_v4_pb->set_name(own_v4.name); own_v4_pb->set_age(own_v4.age);
    pb_pet.clear_arr_own_v4(); for (size_t i = 0; i < arr_own_v4.size(); ++i) { auto* a = pb_pet.add_arr_own_v4(); a->set_name(arr_own_v4[i].name); a->set_age(arr_own_v4[i].age); } // size 10
    pb_pet.clear_vec_own_v4(); for (auto& o : vec_own_v4) { auto* v = pb_pet.add_vec_own_v4(); v->set_name(o.name); v->set_age(o.age); }
    // Enums
    pb_pet.set_pet_type(static_cast<benchmark::pb::PetType>(pet_type));
    pb_pet.clear_arr_pet_type(); for (size_t i = 0; i < arr_pet_type.size(); ++i) pb_pet.add_arr_pet_type(static_cast<benchmark::pb::PetType>(arr_pet_type[i])); // size 2
    pb_pet.clear_vec_pet_type(); for (auto v : vec_pet_type) pb_pet.add_vec_pet_type(static_cast<benchmark::pb::PetType>(v));

    // Fill FastDDS Pet
    idl_pet.d(d); idl_pet.f(f); idl_pet.i32(i32); idl_pet.i64(i64); idl_pet.u32(u32); idl_pet.u64(u64); idl_pet.bval(bval); idl_pet.s(s);
    idl_pet.arr_d(arr_d); idl_pet.arr_f(arr_f); idl_pet.arr_i32(arr_i32); idl_pet.arr_i64(arr_i64); idl_pet.arr_u32(arr_u32); idl_pet.arr_u64(arr_u64); idl_pet.arr_bval(arr_bval); idl_pet.arr_s(arr_s);
    idl_pet.vec_d(vec_d); idl_pet.vec_f(vec_f); idl_pet.vec_i32(vec_i32); idl_pet.vec_i64(vec_i64); idl_pet.vec_u32(vec_u32); idl_pet.vec_u64(vec_u64); idl_pet.vec_bval(vec_bval); idl_pet.vec_s(vec_s);
    idl_pet.arr_u8(arr_u8);
    // Owners
    benchmark::idl::Owner idl_own; idl_own.name(own.name); idl_own.age(own.age);
    idl_pet.own(idl_own);
    std::array<benchmark::idl::Owner, 10> arr_own_idl; for (auto& o : arr_own_idl) { o.name(own.name); o.age(own.age); } idl_pet.arr_own(arr_own_idl);
    std::vector<benchmark::idl::Owner> vec_own_idl(cfg.vec_size); for (auto& o : vec_own_idl) { o.name(own.name); o.age(own.age); } idl_pet.vec_own(vec_own_idl);
    benchmark::idl::OwnerV2 idl_own_v2; idl_own_v2.name(own_v2.name); idl_own_v2.age(own_v2.age);
    idl_pet.own_v2(idl_own_v2);
    std::array<benchmark::idl::OwnerV2, 10> arr_own_v2_idl; for (auto& o : arr_own_v2_idl) { o.name(own_v2.name); o.age(own_v2.age); } idl_pet.arr_own_v2(arr_own_v2_idl);
    std::vector<benchmark::idl::OwnerV2> vec_own_v2_idl(cfg.vec_size); for (auto& o : vec_own_v2_idl) { o.name(own_v2.name); o.age(own_v2.age); } idl_pet.vec_own_v2(vec_own_v2_idl);
    benchmark::idl::OwnerV3 idl_own_v3; idl_own_v3.name(own_v3.name); idl_own_v3.age(own_v3.age);
    idl_pet.own_v3(idl_own_v3);
    std::array<benchmark::idl::OwnerV3, 10> arr_own_v3_idl; for (auto& o : arr_own_v3_idl) { o.name(own_v3.name); o.age(own_v3.age); } idl_pet.arr_own_v3(arr_own_v3_idl);
    std::vector<benchmark::idl::OwnerV3> vec_own_v3_idl(cfg.vec_size); for (auto& o : vec_own_v3_idl) { o.name(own_v3.name); o.age(own_v3.age); } idl_pet.vec_own_v3(vec_own_v3_idl);
    benchmark::idl::OwnerV4 idl_own_v4; idl_own_v4.name(own_v4.name); idl_own_v4.age(own_v4.age);
    idl_pet.own_v4(idl_own_v4);
    std::array<benchmark::idl::OwnerV4, 10> arr_own_v4_idl; for (auto& o : arr_own_v4_idl) { o.name(own_v4.name); o.age(own_v4.age); } idl_pet.arr_own_v4(arr_own_v4_idl);
    std::vector<benchmark::idl::OwnerV4> vec_own_v4_idl(cfg.vec_size); for (auto& o : vec_own_v4_idl) { o.name(own_v4.name); o.age(own_v4.age); } idl_pet.vec_own_v4(vec_own_v4_idl);
    idl_pet.pet_type(static_cast<benchmark::idl::PetType>(pet_type));
    idl_pet.arr_pet_type({static_cast<benchmark::idl::PetType>(arr_pet_type[0]), static_cast<benchmark::idl::PetType>(arr_pet_type[1])});
    idl_pet.vec_pet_type(std::vector<benchmark::idl::PetType>(cfg.vec_size, static_cast<benchmark::idl::PetType>(rf_pet::PetType::FISH)));
}

int main() {
    using namespace ankerl::nanobench;
    std::vector<size_t> test_sizes = {1, 5,10,15,20,25,50, 100, 1000};
    for (size_t sz : test_sizes) {
        PetDataConfig cfg{sz, 16};
        rf_pet::Pet pet;
        benchmark::pb::Pet pb_pet;
        benchmark::idl::Pet idl_pet;
        fill_pet(pet, pb_pet, idl_pet, cfg);
        std::vector<uint8_t> custom_serialized;
        custom_serialized.reserve(2000000);
        std::string pb_serialized;
        pb_serialized.reserve(2000000);
        std::vector<char> idl_buf(2000000);
        std::cout << "\n--- Benchmark for dynamic container size: " << sz << " ---\n";
        Bench().epochs(1).epochIterations(100000).run("Custom dump", [&] {
            custom_serialized.clear();
            pet.dump(custom_serialized);
        });
        Bench().epochs(1).epochIterations(100000).run("Custom load", [&] {
            pet.load(custom_serialized);
        });
        Bench().epochs(1).epochIterations(100000).run("Protobuf serialize", [&] {
            pb_pet.SerializeToString(&pb_serialized);
        });
        Bench().epochs(1).epochIterations(100000).run("Protobuf deserialize", [&] {
            pb_pet.ParseFromString(pb_serialized);
        });
        Bench().epochs(1).epochIterations(100000).run("FastDDS serialize", [&] {
            eprosima::fastcdr::FastBuffer cdrbuffer(idl_buf.data(), idl_buf.size());
            eprosima::fastcdr::Cdr ser(cdrbuffer);
            idl_pet.serialize(ser);
        });
        Bench().epochs(1).epochIterations(100000).run("FastDDS deserialize", [&] {
            eprosima::fastcdr::FastBuffer cdrbuffer(idl_buf.data(), idl_buf.size());
            eprosima::fastcdr::Cdr deser(cdrbuffer);
            idl_pet.deserialize(deser);
        });
    }
    return 0;
} 