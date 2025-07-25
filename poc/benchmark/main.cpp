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

// Helper to fill random Owner
rf_owner::Owner make_random_owner() {
    rf_owner::Owner o;
    o.name = random_string(10);
    o.age = 30;
    return o;
}
rf_owner::OwnerV2 make_random_owner_v2() {
    rf_owner::OwnerV2 o;
    o.name = random_string(10);
    o.age = 31;
    return o;
}
rf_owner::nested::OwnerV3 make_random_owner_v3() {
    rf_owner::nested::OwnerV3 o;
    o.name = random_string(10);
    o.age = 32;
    return o;
}
OwnerV4 make_random_owner_v4() {
    OwnerV4 o;
    o.name = random_string(10);
    o.age = 33;
    return o;
}

// Helper for PetType enum
rf_pet::PetType random_pet_type() {
    return static_cast<rf_pet::PetType>(std::rand() % 10);
}

// Fill our C++ Pet
rf_pet::Pet make_random_pet() {
    rf_pet::Pet pet;
    pet.d = 3.14;
    pet.f = 2.71f;
    pet.i32 = 42;
    pet.i64 = 1234567890123;
    pet.u32 = 123456;
    pet.u64 = 9876543210ULL;
    pet.bval = true;
    pet.s = random_string(16);
    pet.arr_d = {1.1, 2.2};
    pet.arr_f = {3.3f, 4.4f};
    pet.arr_i32 = {5, 6};
    pet.arr_i64 = {7, 8};
    pet.arr_u32 = {9, 10};
    pet.arr_u64 = {11, 12};
    pet.arr_bval = {true, false};
    pet.arr_s = {random_string(8), random_string(8)};
    pet.vec_d = {1.1, 2.2, 3.3};
    pet.vec_f = {4.4f, 5.5f};
    pet.vec_i32 = {6, 7, 8};
    pet.vec_i64 = {9, 10};
    pet.vec_u32 = {11, 12};
    pet.vec_u64 = {13, 14};
    pet.vec_bval = {true, false, true};
    pet.vec_s = {random_string(6), random_string(6)};
    pet.arr_u8.fill(0xAB);
    // Owners
    pet.own = make_random_owner();
    for (auto& o : pet.arr_own) o = make_random_owner();
    pet.vec_own = {make_random_owner(), make_random_owner()};
    pet.own_v2 = make_random_owner_v2();
    for (auto& o : pet.arr_own_v2) o = make_random_owner_v2();
    pet.vec_own_v2 = {make_random_owner_v2(), make_random_owner_v2()};
    pet.own_v3 = make_random_owner_v3();
    for (auto& o : pet.arr_own_v3) o = make_random_owner_v3();
    pet.vec_own_v3 = {make_random_owner_v3(), make_random_owner_v3()};
    pet.own_v4 = make_random_owner_v4();
    for (auto& o : pet.arr_own_v4) o = make_random_owner_v4();
    pet.vec_own_v4 = {make_random_owner_v4(), make_random_owner_v4()};
    // Enums
    pet.pet_type = random_pet_type();
    pet.arr_pet_type = {random_pet_type(), random_pet_type()};
    pet.vec_pet_type = {random_pet_type(), random_pet_type()};
    return pet;
}

// Fill protobuf Pet
benchmark::pb::Pet make_random_pb_pet() {
    benchmark::pb::Pet pb_pet;
    pb_pet.set_d(3.14);
    pb_pet.set_f(2.71f);
    pb_pet.set_i32(42);
    pb_pet.set_i64(1234567890123);
    pb_pet.set_u32(123456);
    pb_pet.set_u64(9876543210ULL);
    pb_pet.set_bval(true);
    pb_pet.set_s(random_string(16));
    pb_pet.add_arr_d(1.1); pb_pet.add_arr_d(2.2);
    pb_pet.add_arr_f(3.3f); pb_pet.add_arr_f(4.4f);
    pb_pet.add_arr_i32(5); pb_pet.add_arr_i32(6);
    pb_pet.add_arr_i64(7); pb_pet.add_arr_i64(8);
    pb_pet.add_arr_u32(9); pb_pet.add_arr_u32(10);
    pb_pet.add_arr_u64(11); pb_pet.add_arr_u64(12);
    pb_pet.add_arr_bval(true); pb_pet.add_arr_bval(false);
    pb_pet.add_arr_s(random_string(8)); pb_pet.add_arr_s(random_string(8));
    pb_pet.add_vec_d(1.1); pb_pet.add_vec_d(2.2); pb_pet.add_vec_d(3.3);
    pb_pet.add_vec_f(4.4f); pb_pet.add_vec_f(5.5f);
    pb_pet.add_vec_i32(6); pb_pet.add_vec_i32(7); pb_pet.add_vec_i32(8);
    pb_pet.add_vec_i64(9); pb_pet.add_vec_i64(10);
    pb_pet.add_vec_u32(11); pb_pet.add_vec_u32(12);
    pb_pet.add_vec_u64(13); pb_pet.add_vec_u64(14);
    pb_pet.add_vec_bval(true); pb_pet.add_vec_bval(false); pb_pet.add_vec_bval(true);
    pb_pet.add_vec_s(random_string(6)); pb_pet.add_vec_s(random_string(6));
    pb_pet.set_arr_u8(std::string(100, '\xAB'));
    // Owners
    auto* own = pb_pet.mutable_own();
    own->set_name(random_string(10)); own->set_age(30);
    for (int i = 0; i < 10; ++i) {
        auto* arr_own = pb_pet.add_arr_own();
        arr_own->set_name(random_string(10)); arr_own->set_age(30);
    }
    for (int i = 0; i < 2; ++i) {
        auto* vec_own = pb_pet.add_vec_own();
        vec_own->set_name(random_string(10)); vec_own->set_age(30);
    }
    auto* own_v2 = pb_pet.mutable_own_v2();
    own_v2->set_name(random_string(10)); own_v2->set_age(31);
    for (int i = 0; i < 10; ++i) {
        auto* arr_own_v2 = pb_pet.add_arr_own_v2();
        arr_own_v2->set_name(random_string(10)); arr_own_v2->set_age(31);
    }
    for (int i = 0; i < 2; ++i) {
        auto* vec_own_v2 = pb_pet.add_vec_own_v2();
        vec_own_v2->set_name(random_string(10)); vec_own_v2->set_age(31);
    }
    auto* own_v3 = pb_pet.mutable_own_v3();
    own_v3->set_name(random_string(10)); own_v3->set_age(32);
    for (int i = 0; i < 10; ++i) {
        auto* arr_own_v3 = pb_pet.add_arr_own_v3();
        arr_own_v3->set_name(random_string(10)); arr_own_v3->set_age(32);
    }
    for (int i = 0; i < 2; ++i) {
        auto* vec_own_v3 = pb_pet.add_vec_own_v3();
        vec_own_v3->set_name(random_string(10)); vec_own_v3->set_age(32);
    }
    auto* own_v4 = pb_pet.mutable_own_v4();
    own_v4->set_name(random_string(10)); own_v4->set_age(33);
    for (int i = 0; i < 10; ++i) {
        auto* arr_own_v4 = pb_pet.add_arr_own_v4();
        arr_own_v4->set_name(random_string(10)); arr_own_v4->set_age(33);
    }
    for (int i = 0; i < 2; ++i) {
        auto* vec_own_v4 = pb_pet.add_vec_own_v4();
        vec_own_v4->set_name(random_string(10)); vec_own_v4->set_age(33);
    }
    // Enums
    pb_pet.set_pet_type(static_cast<benchmark::pb::PetType>(std::rand() % 10));
    pb_pet.add_arr_pet_type(static_cast<benchmark::pb::PetType>(std::rand() % 10));
    pb_pet.add_arr_pet_type(static_cast<benchmark::pb::PetType>(std::rand() % 10));
    pb_pet.add_vec_pet_type(static_cast<benchmark::pb::PetType>(std::rand() % 10));
    pb_pet.add_vec_pet_type(static_cast<benchmark::pb::PetType>(std::rand() % 10));
    return pb_pet;
}

// Fill FastDDS Pet
benchmark::idl::Pet make_random_idl_pet() {
    benchmark::idl::Pet idl_pet;
    idl_pet.d(3.14);
    idl_pet.f(2.71f);
    idl_pet.i32(42);
    idl_pet.i64(1234567890123);
    idl_pet.u32(123456);
    idl_pet.u64(9876543210ULL);
    idl_pet.bval(true);
    idl_pet.s(random_string(16));
    idl_pet.arr_d({1.1, 2.2});
    idl_pet.arr_f({3.3f, 4.4f});
    idl_pet.arr_i32({5, 6});
    idl_pet.arr_i64({7, 8});
    idl_pet.arr_u32({9, 10});
    idl_pet.arr_u64({11, 12});
    idl_pet.arr_bval({true, false});
    idl_pet.arr_s({random_string(8), random_string(8)});
    idl_pet.vec_d({1.1, 2.2, 3.3});
    idl_pet.vec_f({4.4f, 5.5f});
    idl_pet.vec_i32({6, 7, 8});
    idl_pet.vec_i64({9, 10});
    idl_pet.vec_u32({11, 12});
    idl_pet.vec_u64({13, 14});
    idl_pet.vec_bval({true, false, true});
    idl_pet.vec_s({random_string(6), random_string(6)});
    idl_pet.arr_u8({}); idl_pet.arr_u8().fill(0xAB);
    // Owners
    benchmark::idl::Owner own; own.name(random_string(10)); own.age(30); idl_pet.own(own);
    std::array<benchmark::idl::Owner, 10> arr_own; for (auto& o : arr_own) { o.name(random_string(10)); o.age(30); } idl_pet.arr_own(arr_own);
    std::vector<benchmark::idl::Owner> vec_own = {own, own}; idl_pet.vec_own(vec_own);
    benchmark::idl::OwnerV2 own_v2; own_v2.name(random_string(10)); own_v2.age(31); idl_pet.own_v2(own_v2);
    std::array<benchmark::idl::OwnerV2, 10> arr_own_v2; for (auto& o : arr_own_v2) { o.name(random_string(10)); o.age(31); } idl_pet.arr_own_v2(arr_own_v2);
    std::vector<benchmark::idl::OwnerV2> vec_own_v2 = {own_v2, own_v2}; idl_pet.vec_own_v2(vec_own_v2);
    benchmark::idl::OwnerV3 own_v3; own_v3.name(random_string(10)); own_v3.age(32); idl_pet.own_v3(own_v3);
    std::array<benchmark::idl::OwnerV3, 10> arr_own_v3; for (auto& o : arr_own_v3) { o.name(random_string(10)); o.age(32); } idl_pet.arr_own_v3(arr_own_v3);
    std::vector<benchmark::idl::OwnerV3> vec_own_v3 = {own_v3, own_v3}; idl_pet.vec_own_v3(vec_own_v3);
    benchmark::idl::OwnerV4 own_v4; own_v4.name(random_string(10)); own_v4.age(33); idl_pet.own_v4(own_v4);
    std::array<benchmark::idl::OwnerV4, 10> arr_own_v4; for (auto& o : arr_own_v4) { o.name(random_string(10)); o.age(33); } idl_pet.arr_own_v4(arr_own_v4);
    std::vector<benchmark::idl::OwnerV4> vec_own_v4 = {own_v4, own_v4}; idl_pet.vec_own_v4(vec_own_v4);
    // Enums
    idl_pet.pet_type(static_cast<benchmark::idl::PetType>(std::rand() % 10));
    idl_pet.arr_pet_type({static_cast<benchmark::idl::PetType>(std::rand() % 10), static_cast<benchmark::idl::PetType>(std::rand() % 10)});
    idl_pet.vec_pet_type({static_cast<benchmark::idl::PetType>(std::rand() % 10), static_cast<benchmark::idl::PetType>(std::rand() % 10)});
    return idl_pet;
}

int main() {
    using namespace ankerl::nanobench;
    // --- Custom impl ---
    rf_pet::Pet pet = make_random_pet();
    std::string custom_serialized;
    Bench().epochs(1).epochIterations(1000000).run("Custom dump", [&] {
        custom_serialized = pet.dump();
    });
    Bench().epochs(1).epochIterations(1000000).run("Custom load", [&] {
        rf_pet::Pet p2; p2.load(custom_serialized);
    });

    // --- Protobuf ---
    benchmark::pb::Pet pb_pet = make_random_pb_pet();
    std::string pb_serialized;
    Bench().epochs(1).epochIterations(1000000).run("Protobuf serialize", [&] {
        pb_pet.SerializeToString(&pb_serialized);
    });
    Bench().epochs(1).epochIterations(1000000).run("Protobuf deserialize", [&] {
        benchmark::pb::Pet pb2; pb2.ParseFromString(pb_serialized);
    });

    // --- FastDDS/IDL ---
    benchmark::idl::Pet idl_pet = make_random_idl_pet();
    std::vector<char> idl_buf(200000); // Large enough buffer
    Bench().epochs(1).epochIterations(1000000).run("FastDDS serialize", [&] {
        eprosima::fastcdr::FastBuffer cdrbuffer(idl_buf.data(), idl_buf.size());
        eprosima::fastcdr::Cdr ser(cdrbuffer);
        idl_pet.serialize(ser);
    });
    Bench().epochs(1).epochIterations(1000000).run("FastDDS deserialize", [&] {
        eprosima::fastcdr::FastBuffer cdrbuffer(idl_buf.data(), idl_buf.size());
        eprosima::fastcdr::Cdr deser(cdrbuffer);
        benchmark::idl::Pet idl2; idl2.deserialize(deser);
    });
    return 0;
} 