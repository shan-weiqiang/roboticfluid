#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <random>
#include <fstream>
#include <memory>
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
    std::array<double, 10000> arr_d = {1.1};
    std::array<float, 10000> arr_f = {3.3f};
    std::array<int32_t, 10000> arr_i32 = {5};
    std::array<int64_t, 10000> arr_i64 = {7};
    std::array<uint32_t, 10000> arr_u32 = {9};
    std::array<uint64_t, 10000> arr_u64 = {11};
    std::array<bool, 10000> arr_bval = {true};
    std::array<std::string, 10000> arr_s = {random_string(cfg.str_len)};
    std::vector<double> vec_d(cfg.vec_size, 1.23);
    std::vector<float> vec_f(cfg.vec_size, 2.34f);
    std::vector<int32_t> vec_i32(cfg.vec_size, 123);
    std::vector<int64_t> vec_i64(cfg.vec_size, 456789);
    std::vector<uint32_t> vec_u32(cfg.vec_size, 987);
    std::vector<uint64_t> vec_u64(cfg.vec_size, 654321);
    std::vector<bool> vec_bval(cfg.vec_size, true);
    std::vector<std::string> vec_s(cfg.vec_size, random_string(cfg.str_len));
    std::array<uint8_t, 10000> arr_u8; arr_u8.fill(0xAB);
    // Owners
    rf_owner::Owner own; own.name = "owner"; own.age = 30;
    std::array<rf_owner::Owner, 10000> arr_own; for (auto& o : arr_own) { o.name = "owner"; o.age = 30; }
    std::vector<rf_owner::Owner> vec_own(cfg.vec_size, own);
    rf_owner::OwnerV2 own_v2; own_v2.name = "ownerv2"; own_v2.age = 31;
    std::array<rf_owner::OwnerV2, 10000> arr_own_v2; for (auto& o : arr_own_v2) { o.name = "ownerv2"; o.age = 31; }
    std::vector<rf_owner::OwnerV2> vec_own_v2(cfg.vec_size, own_v2);
    rf_owner::nested::OwnerV3 own_v3; own_v3.name = "ownerv3"; own_v3.age = 32;
    std::array<rf_owner::nested::OwnerV3, 10000> arr_own_v3; for (auto& o : arr_own_v3) { o.name = "ownerv3"; o.age = 32; }
    std::vector<rf_owner::nested::OwnerV3> vec_own_v3(cfg.vec_size, own_v3);
    OwnerV4 own_v4; own_v4.name = "ownerv4"; own_v4.age = 33;
    std::array<OwnerV4, 10000> arr_own_v4; for (auto& o : arr_own_v4) { o.name = "ownerv4"; o.age = 33; }
    std::vector<OwnerV4> vec_own_v4(cfg.vec_size, own_v4);
    // Enums
    rf_pet::PetType pet_type = rf_pet::PetType::DOG;
    std::array<rf_pet::PetType, 10000> arr_pet_type = {rf_pet::PetType::CAT};
    std::vector<rf_pet::PetType> vec_pet_type(cfg.vec_size, rf_pet::PetType::FISH);

    // Fill custom Pet
    pet.d = d; pet.f = f; pet.i32 = i32; pet.i64 = i64; pet.u32 = u32; pet.u64 = u64; pet.bval = bval; pet.s = s;
    pet.set_arr_d(arr_d); pet.set_arr_f(arr_f); pet.set_arr_i32(arr_i32); pet.set_arr_i64(arr_i64); pet.set_arr_u32(arr_u32); pet.set_arr_u64(arr_u64); pet.set_arr_bval(arr_bval); pet.set_arr_s(arr_s);
    pet.vec_d = vec_d; pet.vec_f = vec_f; pet.vec_i32 = vec_i32; pet.vec_i64 = vec_i64; pet.vec_u32 = vec_u32; pet.vec_u64 = vec_u64; pet.vec_bval = vec_bval; pet.vec_s = vec_s;
    pet.set_arr_u8(arr_u8);
    pet.own = own; pet.set_arr_own(arr_own); pet.vec_own = vec_own;
    pet.own_v2 = own_v2; pet.set_arr_own_v2(arr_own_v2); pet.vec_own_v2 = vec_own_v2;
    pet.own_v3 = own_v3; pet.set_arr_own_v3(arr_own_v3); pet.vec_own_v3 = vec_own_v3;
    pet.own_v4 = own_v4; pet.set_arr_own_v4(arr_own_v4); pet.vec_own_v4 = vec_own_v4;
    pet.pet_type = pet_type; pet.set_arr_pet_type(arr_pet_type); pet.vec_pet_type = vec_pet_type;

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
    std::array<benchmark::idl::Owner, 10000> arr_own_idl; for (auto& o : arr_own_idl) { o.name(own.name); o.age(own.age); } idl_pet.arr_own(arr_own_idl);
    std::vector<benchmark::idl::Owner> vec_own_idl(cfg.vec_size); for (auto& o : vec_own_idl) { o.name(own.name); o.age(own.age); } idl_pet.vec_own(vec_own_idl);
    benchmark::idl::OwnerV2 idl_own_v2; idl_own_v2.name(own_v2.name); idl_own_v2.age(own_v2.age);
    idl_pet.own_v2(idl_own_v2);
    std::array<benchmark::idl::OwnerV2, 10000> arr_own_v2_idl; for (auto& o : arr_own_v2_idl) { o.name(own_v2.name); o.age(own_v2.age); } idl_pet.arr_own_v2(arr_own_v2_idl);
    std::vector<benchmark::idl::OwnerV2> vec_own_v2_idl(cfg.vec_size); for (auto& o : vec_own_v2_idl) { o.name(own_v2.name); o.age(own_v2.age); } idl_pet.vec_own_v2(vec_own_v2_idl);
    benchmark::idl::OwnerV3 idl_own_v3; idl_own_v3.name(own_v3.name); idl_own_v3.age(own_v3.age);
    idl_pet.own_v3(idl_own_v3);
    std::array<benchmark::idl::OwnerV3, 10000> arr_own_v3_idl; for (auto& o : arr_own_v3_idl) { o.name(own_v3.name); o.age(own_v3.age); } idl_pet.arr_own_v3(arr_own_v3_idl);
    std::vector<benchmark::idl::OwnerV3> vec_own_v3_idl(cfg.vec_size); for (auto& o : vec_own_v3_idl) { o.name(own_v3.name); o.age(own_v3.age); } idl_pet.vec_own_v3(vec_own_v3_idl);
    benchmark::idl::OwnerV4 idl_own_v4; idl_own_v4.name(own_v4.name); idl_own_v4.age(own_v4.age);
    idl_pet.own_v4(idl_own_v4);
    std::array<benchmark::idl::OwnerV4, 10000> arr_own_v4_idl; for (auto& o : arr_own_v4_idl) { o.name(own_v4.name); o.age(own_v4.age); } idl_pet.arr_own_v4(arr_own_v4_idl);
    std::vector<benchmark::idl::OwnerV4> vec_own_v4_idl(cfg.vec_size); for (auto& o : vec_own_v4_idl) { o.name(own_v4.name); o.age(own_v4.age); } idl_pet.vec_own_v4(vec_own_v4_idl);
    idl_pet.pet_type(static_cast<benchmark::idl::PetType>(pet_type));
    idl_pet.arr_pet_type({static_cast<benchmark::idl::PetType>(arr_pet_type[0]), static_cast<benchmark::idl::PetType>(arr_pet_type[1])});
    idl_pet.vec_pet_type(std::vector<benchmark::idl::PetType>(cfg.vec_size, static_cast<benchmark::idl::PetType>(rf_pet::PetType::FISH)));
}


// Human-readable size
std::string human_readable_size(size_t bytes) {
    const char* suffixes[] = {"B", "KB", "MB", "GB"};
    size_t i = 0;
    double count = bytes;
    while (count >= 1024 && i < 3) {
        count /= 1024;
        ++i;
    }
    char buf[32];
    snprintf(buf, sizeof(buf), "%.2f %s", count, suffixes[i]);
    return std::string(buf);
}

// Test correctness of roboticfluid serialization/deserialization
bool test_correctness(const rf_pet::Pet& original_pet, const std::string& test_name) {
    std::cout << "Testing roboticfluid correctness for " << test_name << "..." << std::endl;
    
    // Test 1: Dump -> Load -> Compare
    std::vector<uint8_t> serialized;
    serialized.reserve(20 * 1024 * 1024); // 20MB
    
    // Dump the original pet using roboticfluid
    original_pet.dump(serialized);
    std::cout << "  Roboticfluid serialized size: " << human_readable_size(serialized.size()) << std::endl;
    
    // Load into a new pet using roboticfluid
    auto loaded_pet = std::make_unique<rf_pet::Pet>();
    loaded_pet->load(serialized);
    
    // Compare original with loaded (check key fields)
    bool test1_passed = true;
    test1_passed &= (loaded_pet->d == original_pet.d);
    test1_passed &= (loaded_pet->f == original_pet.f);
    test1_passed &= (loaded_pet->i32 == original_pet.i32);
    test1_passed &= (loaded_pet->i64 == original_pet.i64);
    test1_passed &= (loaded_pet->u32 == original_pet.u32);
    test1_passed &= (loaded_pet->u64 == original_pet.u64);
    test1_passed &= (loaded_pet->bval == original_pet.bval);
    test1_passed &= (loaded_pet->s == original_pet.s);
    test1_passed &= (loaded_pet->vec_d.size() == original_pet.vec_d.size());
    test1_passed &= (loaded_pet->vec_s.size() == original_pet.vec_s.size());
    
    std::cout << "  Test 1 (roboticfluid dump->load->compare): " << (test1_passed ? "PASSED" : "FAILED") << std::endl;
    
    // Test 2: Reuse same variable - Load again into loaded_pet
    loaded_pet->load(serialized);
    
    // Compare with the original (check key fields)
    bool test2_passed = true;
    test2_passed &= (loaded_pet->d == original_pet.d);
    test2_passed &= (loaded_pet->f == original_pet.f);
    test2_passed &= (loaded_pet->i32 == original_pet.i32);
    test2_passed &= (loaded_pet->i64 == original_pet.i64);
    test2_passed &= (loaded_pet->u32 == original_pet.u32);
    test2_passed &= (loaded_pet->u64 == original_pet.u64);
    test2_passed &= (loaded_pet->bval == original_pet.bval);
    test2_passed &= (loaded_pet->s == original_pet.s);
    test2_passed &= (loaded_pet->vec_d.size() == original_pet.vec_d.size());
    test2_passed &= (loaded_pet->vec_s.size() == original_pet.vec_s.size());
    
    std::cout << "  Test 2 (roboticfluid reuse same variable): " << (test2_passed ? "PASSED" : "FAILED") << std::endl;
    
    bool all_passed = test1_passed && test2_passed;
    std::cout << "  Overall roboticfluid result: " << (all_passed ? "PASSED" : "FAILED") << std::endl;
    std::cout << std::endl;
    
    return all_passed;
}


int main() {
    using namespace ankerl::nanobench;
    
    // Create output files
    std::ofstream markdown_file("benchmark_results.md");
    std::ofstream csv_file("benchmark_results.csv");
    std::ofstream json_file("benchmark_results.json");
    
    // Create a bench instance that will collect all results
    Bench bench;
    bench.output(&markdown_file); // Redirect default output to markdown file
    
    std::vector<size_t> test_sizes = {
        1, 10, 50, 100, 200, 500, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 
        10000, 15000, 20000, 25000, 30000, 35000, 40000, 45000, 50000, 55000, 60000, 
        65000,  90000
    };
    
    // Test correctness first with a few sample sizes
    std::cout << "=== Testing Correctness ===" << std::endl;
    std::vector<size_t> correctness_test_sizes = {1, 100, 1000, 10000};
    for (size_t sz : correctness_test_sizes) {
        PetDataConfig cfg{sz, 16};
        auto test_pet = std::make_unique<rf_pet::Pet>();
        benchmark::pb::Pet dummy_pb_pet;
        benchmark::idl::Pet dummy_idl_pet;
        fill_pet(*test_pet, dummy_pb_pet, dummy_idl_pet, cfg);
        
        if (!test_correctness(*test_pet, "size " + std::to_string(sz))) {
            std::cerr << "Correctness test failed! Aborting benchmark." << std::endl;
            return 1;
        }
    }
    std::cout << "All correctness tests passed! Proceeding with benchmark..." << std::endl << std::endl;
    
    for (size_t sz : test_sizes) {
        PetDataConfig cfg{sz, 16};
        auto pet = std::make_unique<rf_pet::Pet>();
        benchmark::pb::Pet pb_pet;
        benchmark::idl::Pet idl_pet;
        fill_pet(*pet, pb_pet, idl_pet, cfg);
        
        // Calculate real serialization sizes using FastDDS API
        size_t fastdds_size = benchmark::idl::Pet::getCdrSerializedSize(idl_pet) + 4; // +4 for encapsulation
        size_t protobuf_size = pb_pet.ByteSizeLong();
        
        // Calculate custom serialization size by actually serializing
        std::vector<uint8_t> temp_serialized;
        temp_serialized.reserve(40 * 1024 * 1024); // 20MB
        pet->dump(temp_serialized);
        size_t custom_size = temp_serialized.size();
        
        // Calculate compressed serialization size
        std::vector<uint8_t> temp_compressed;
        temp_compressed.reserve(40 * 1024 * 1024); // 40MB
        pet->dump_compressed(temp_compressed);
        size_t compressed_size = temp_compressed.size();
        
        // Calculate and display compression statistics
        if (!temp_compressed.empty()) {
            double compression_ratio = (1.0 - static_cast<double>(temp_compressed.size()) / custom_size) * 100.0;
            std::cout << "Compression ratio: " << compression_ratio << "%" << std::endl;
            std::cout << "Compressed size: " << human_readable_size(temp_compressed.size()) << " (" << temp_compressed.size() << " bytes)" << std::endl;
            std::cout << "Uncompressed size: " << human_readable_size(custom_size) << " (" << custom_size << " bytes)" << std::endl;
        }
        
        // Use FastDDS size as the reference for data size
        size_t real_size = fastdds_size;
        
        std::cout << "Serialization sizes:" << std::endl;
        std::cout << "  FastDDS: " << human_readable_size(fastdds_size) << " (" << fastdds_size << " bytes)" << std::endl;
        std::cout << "  Protobuf: " << human_readable_size(protobuf_size) << " (" << protobuf_size << " bytes)" << std::endl;
        std::cout << "  Roboticfluid (uncompressed): " << human_readable_size(custom_size) << " (" << custom_size << " bytes)" << std::endl;
        std::cout << "  Roboticfluid (compressed): " << human_readable_size(compressed_size) << " (" << compressed_size << " bytes)" << std::endl;
        std::cout << "  Using FastDDS size as reference: " << human_readable_size(real_size) << " (" << real_size << " bytes)" << std::endl;
        
        std::vector<uint8_t> custom_serialized;
        custom_serialized.reserve(20 * 1024 * 1024); // 20MB
        std::string pb_serialized;
        pb_serialized.reserve(20 * 1024 * 1024); // 20MB
        std::vector<char> idl_buf(2000000);
        idl_buf.resize(20 * 1024 * 1024); // 20MB
        std::cout << "\n--- Benchmark for data size: " << human_readable_size(real_size) << " (" << real_size << " bytes) ---\n";
        
        // Add context information about the data sizes
        bench.context("data_size_bytes", std::to_string(real_size));
        bench.context("data_size_mb", std::to_string(real_size / (1024.0 * 1024.0)));
        bench.context("data_size_human", human_readable_size(real_size));
        bench.context("container_size", std::to_string(sz));  // sz is the container size
        bench.context("fastdds_size_bytes", std::to_string(fastdds_size));
        bench.context("protobuf_size_bytes", std::to_string(protobuf_size));
        bench.context("custom_size_bytes", std::to_string(custom_size));
        bench.context("compressed_size_bytes", std::to_string(compressed_size));
        
        // Keep original format but with milliseconds time unit
        bench.unit("op").batch(1.0);
        
        bench.epochs(1).epochIterations(100).run("roboticfluid dump", [&] {
            custom_serialized.clear();
            pet->dump(custom_serialized);
        });
        bench.epochs(1).epochIterations(100).run("roboticfluid load", [&] {
            auto fresh_pet = std::make_unique<rf_pet::Pet>();
            fresh_pet->load(custom_serialized);
        });
        bench.epochs(1).epochIterations(100).run("roboticfluid dump+compress", [&] {
            temp_compressed.clear();
            pet->dump_compressed(temp_compressed);
        });
        bench.epochs(1).epochIterations(100).run("roboticfluid decompress+load", [&] {
            auto fresh_pet = std::make_unique<rf_pet::Pet>();
            fresh_pet->load_compressed(temp_compressed);
        });
        bench.epochs(1).epochIterations(100).run("Protobuf serialize", [&] {
            pb_pet.SerializeToString(&pb_serialized);
        });
        bench.epochs(1).epochIterations(100).run("Protobuf deserialize", [&] {
            benchmark::pb::Pet fresh_pb_pet;
            fresh_pb_pet.ParseFromString(pb_serialized);
        });
        bench.epochs(1).epochIterations(100).run("FastDDS serialize", [&] {
            eprosima::fastcdr::FastBuffer cdrbuffer(idl_buf.data(), idl_buf.size());
            eprosima::fastcdr::Cdr ser(cdrbuffer);
            idl_pet.serialize(ser);
        });
        bench.epochs(1).epochIterations(100).run("FastDDS deserialize", [&] {
            benchmark::idl::Pet fresh_idl_pet;
            eprosima::fastcdr::FastBuffer cdrbuffer(idl_buf.data(), idl_buf.size());
            eprosima::fastcdr::Cdr deser(cdrbuffer);
            fresh_idl_pet.deserialize(deser);
        });
    }
    
    // Output results in different formats
    std::cout << "Writing results to files..." << std::endl;
    
    // Custom CSV format with data size column
    const char* custom_csv_template = R"DELIM("title";"name";"unit";"batch";"data_size_mb";"container_size";"protobuf_size_bytes";"roboticfluid_size_bytes";"roboticfluid_compressed_size_bytes";"elapsed_ns";"total"
{{#result}}"{{title}}";"{{name}}";"{{unit}}";{{batch}};{{context(data_size_mb)}};{{context(container_size)}};{{context(protobuf_size_bytes)}};{{context(custom_size_bytes)}};{{context(compressed_size_bytes)}};{{median(elapsed)}};{{sumProduct(iterations, elapsed)}}
{{/result}})DELIM";
    
    bench.render(custom_csv_template, csv_file);
    
    // JSON format
    bench.render(templates::json(), json_file);
    
    // Close files
    markdown_file.close();
    csv_file.close();
    json_file.close();
    
    std::cout << "Results written to:" << std::endl;
    std::cout << "  - benchmark_results.md (markdown table)" << std::endl;
    std::cout << "  - benchmark_results.csv (CSV format)" << std::endl;
    std::cout << "  - benchmark_results.json (JSON format)" << std::endl;
    
    return 0;
} 