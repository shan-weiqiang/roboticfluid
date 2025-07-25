#include <iostream>
#include <cassert>
#include <vector>
#include <string>
#include <array>
#include <memory>
#include "roboticfluid_cpp/rf_pet/pet.hpp"
#include "roboticfluid_cpp/rf_owner/owner.hpp"

using namespace rf_pet;
using namespace rf_owner;

int main() {
    std::cout << "\n=== Testing basic Pet and Owner functionality ===\n";

    // Create an owner
    Owner owner;
    owner.set_name("John Doe");
    owner.set_age(20);
    std::cout << "Created owner: " << owner.get_name() << " (age: " << owner.get_age() << ")\n";

    // Create a pet
    auto pet = std::make_unique<rf_pet::Pet>();
    pet->set_s("Buddy");
    pet->set_i32(5);
    pet->set_f(25.5);
    pet->set_d(45.2);
    pet->set_own(owner);

    // Set some arrays and vectors
    std::array<double, 10000> arr_d = {1.1, 2.2};
    arr_d[1] = 2.2;
    pet->set_arr_d(arr_d);
    std::array<float, 10000> arr_f = {3.3f, 4.4f};
    arr_f[1] = 4.4f;
    pet->set_arr_f(arr_f);
    std::array<int32_t, 10000> arr_i32 = {10, 20};
    arr_i32[1] = 20;
    pet->set_arr_i32(arr_i32);
    std::array<int64_t, 10000> arr_i64 = {100, 200};
    arr_i64[1] = 200;
    pet->set_arr_i64(arr_i64);
    std::array<uint32_t, 10000> arr_u32 = {1000, 2000};
    arr_u32[1] = 2000;
    pet->set_arr_u32(arr_u32);
    std::array<uint64_t, 10000> arr_u64 = {10000, 20000};
    arr_u64[1] = 20000;
    pet->set_arr_u64(arr_u64);
    std::array<bool, 10000> arr_bval = {true, false};
    arr_bval[1] = false;
    pet->set_arr_bval(arr_bval);
    std::array<std::string, 10000> arr_s = {"a", "b"};
    arr_s[1] = "b";
    pet->set_arr_s(arr_s);
    pet->set_vec_d({5.5, 6.6, 7.7});
    pet->set_vec_f({8.8f, 9.9f});
    pet->set_vec_i32({30, 40, 50});
    pet->set_vec_i64({300, 400});
    pet->set_vec_u32({3000, 4000});
    pet->set_vec_u64({30000, 40000});
    pet->set_vec_bval({false, true, true});
    pet->set_vec_s({"x", "y", "z"});

    // Set arr_u8
    std::array<uint8_t, 10000> arr_u8;
    for (int i = 0; i < 10000; ++i) arr_u8[i] = static_cast<uint8_t>(i % 256);
    pet->set_arr_u8(arr_u8);
    std::cout << "Pet arr_u8: [";
    for (int i = 0; i < 10; ++i) std::cout << int(pet->get_arr_u8()[i]) << (i < 9 ? ", " : "");
    std::cout << "] ... (len=" << pet->get_arr_u8().size() << ")\n";

    std::cout << "Created pet: " << pet->get_s() << " (age: " << pet->get_i32() << ", weight: " << pet->get_f() << ")\n";
    std::cout << "Pet owner: " << pet->get_own().get_name() << "\n";
    std::cout << "Pet tricks: ";
    for (const auto& s : pet->get_vec_s()) std::cout << s << " ";
    std::cout << "\nPet favorite numbers: ";
    for (const auto& n : pet->get_arr_i32()) std::cout << n << " ";
    std::cout << "\n";

    // Test enum functionality
    pet->set_pet_type(PetType::DOG);
    pet->set_arr_pet_type({PetType::CAT, PetType::BIRD});
    pet->set_vec_pet_type({PetType::FISH, PetType::HAMSTER, PetType::RABBIT});
    std::cout << "Pet type: " << int(pet->get_pet_type()) << "\n";
    std::cout << "Pet type array: [" << int(pet->get_arr_pet_type()[0]) << ", " << int(pet->get_arr_pet_type()[1]) << "]\n";
    std::cout << "Pet type vector: ";
    for (auto t : pet->get_vec_pet_type()) std::cout << int(t) << " ";
    std::cout << "\n";

    // Test the bark method
    std::cout << "\nTesting bark method:\n";
    pet->bark();

    // Test freezing
    std::cout << "\n=== Testing freezing ===\n";
    std::vector<uint8_t> freezed;
    pet->dump(freezed);
    std::cout << "Freezed pet: ";
    for (size_t i = 0; i < std::min<size_t>(16, freezed.size()); ++i)
        std::cout << std::hex << (unsigned int)freezed[i] << " ";
    std::cout << "... (type: std::vector<uint8_t>, size: " << std::dec << freezed.size() << ")\n";

    // Test melting
    std::cout << "\n=== Testing melting ===\n";
    Pet new_pet;
    new_pet.load(freezed);
    new_pet.load(freezed);

    std::cout << "Melted s: " << new_pet.get_s() << "\n";
    std::cout << "Melted i32: " << new_pet.get_i32() << "\n";
    std::cout << "Melted arr_u8[:10]: [";
    for (int i = 0; i < 10; ++i) std::cout << int(new_pet.get_arr_u8()[i]) << (i < 9 ? ", " : "");
    std::cout << "]\n";
    for (int i = 0; i < 10000; ++i) assert(new_pet.get_arr_u8()[i] == i % 256);

    std::cout << "\n=== Testing round-trip freezing/melting ===\n";
    pet->set_s("Fido");
    pet->set_i32(42);
    pet->set_f(12.5);

    pet->dump(freezed);
    std::cout << "Freezed: ";
    for (size_t i = 0; i < std::min<size_t>(16, freezed.size()); ++i)
        std::cout << std::hex << (unsigned int)freezed[i] << " ";
    std::cout << "...\n";
    Pet p;
    p.load(freezed);
    std::cout << "Melted s: " << p.get_s() << "\n";
    std::cout << "Melted i32: " << p.get_i32() << "\n";
    std::cout << "Melted f: " << p.get_f() << "\n";

    assert(p.get_s() == pet->get_s());
    assert(p.get_i32() == pet->get_i32());
    assert(std::abs(p.get_f() - pet->get_f()) < 1e-6);
    std::cout << "\u2713 Round-trip test passed!\n";

    // Test OwnerV2
    rf_owner::OwnerV2 ownerv2;
    ownerv2.set_name("Jane Smith");
    ownerv2.set_age(33);
    pet->set_own_v2(ownerv2);
    std::array<rf_owner::OwnerV2, 10000> arr_own_v2;
    for (int i = 0; i < 10000; ++i) {
        arr_own_v2[i].set_name("ArrOwnerV2" + std::to_string(i));
        arr_own_v2[i].set_age(100 + i);
    }
    pet->set_arr_own_v2(arr_own_v2);
    std::vector<rf_owner::OwnerV2> vec_own_v2(3);
    for (int i = 0; i < 3; ++i) {
        vec_own_v2[i].set_name("VecOwnerV2" + std::to_string(i));
        vec_own_v2[i].set_age(200 + i);
    }
    pet->set_vec_own_v2(vec_own_v2);
    // Test OwnerV3
    rf_owner::nested::OwnerV3 ownerv3;
    ownerv3.set_name("Nested User");
    ownerv3.set_age(44);
    pet->set_own_v3(ownerv3);
    std::array<rf_owner::nested::OwnerV3, 10000> arr_own_v3;
    for (int i = 0; i < 10000; ++i) {
        arr_own_v3[i].set_name("ArrOwnerV3" + std::to_string(i));
        arr_own_v3[i].set_age(110 + i);
    }
    pet->set_arr_own_v3(arr_own_v3);
    std::vector<rf_owner::nested::OwnerV3> vec_own_v3(3);
    for (int i = 0; i < 3; ++i) {
        vec_own_v3[i].set_name("VecOwnerV3" + std::to_string(i));
        vec_own_v3[i].set_age(210 + i);
    }
    pet->set_vec_own_v3(vec_own_v3);
    // Test OwnerV4
    OwnerV4 ownerv4;
    ownerv4.set_name("Top User");
    ownerv4.set_age(55);
    pet->set_own_v4(ownerv4);
    std::array<OwnerV4, 10000> arr_own_v4;
    for (int i = 0; i < 10000; ++i) {
        arr_own_v4[i].set_name("ArrOwnerV4" + std::to_string(i));
        arr_own_v4[i].set_age(120 + i);
    }
    pet->set_arr_own_v4(arr_own_v4);
    std::vector<OwnerV4> vec_own_v4(3);
    for (int i = 0; i < 3; ++i) {
        vec_own_v4[i].set_name("VecOwnerV4" + std::to_string(i));
        vec_own_v4[i].set_age(220 + i);
    }
    pet->set_vec_own_v4(vec_own_v4);

    // After melting, check OwnerV2/3/4 round-trip
    assert(new_pet.get_own_v2().get_name() == "Jane Smith");
    assert(new_pet.get_own_v2().get_age() == 33);
    for (int i = 0; i < 10000; ++i) {
        assert(new_pet.get_arr_own_v2()[i].get_name() == "ArrOwnerV2" + std::to_string(i));
        assert(new_pet.get_arr_own_v2()[i].get_age() == 100 + i);
    }
    for (int i = 0; i < 3; ++i) {
        assert(new_pet.get_vec_own_v2()[i].get_name() == "VecOwnerV2" + std::to_string(i));
        assert(new_pet.get_vec_own_v2()[i].get_age() == 200 + i);
    }
    assert(new_pet.get_own_v3().get_name() == "Nested User");
    assert(new_pet.get_own_v3().get_age() == 44);
    for (int i = 0; i < 10000; ++i) {
        assert(new_pet.get_arr_own_v3()[i].get_name() == "ArrOwnerV3" + std::to_string(i));
        assert(new_pet.get_arr_own_v3()[i].get_age() == 110 + i);
    }
    for (int i = 0; i < 3; ++i) {
        assert(new_pet.get_vec_own_v3()[i].get_name() == "VecOwnerV3" + std::to_string(i));
        assert(new_pet.get_vec_own_v3()[i].get_age() == 210 + i);
    }
    assert(new_pet.get_own_v4().get_name() == "Top User");
    assert(new_pet.get_own_v4().get_age() == 55);
    for (int i = 0; i < 10000; ++i) {
        assert(new_pet.get_arr_own_v4()[i].get_name() == "ArrOwnerV4" + std::to_string(i));
        assert(new_pet.get_arr_own_v4()[i].get_age() == 120 + i);
    }
    for (int i = 0; i < 3; ++i) {
        assert(new_pet.get_vec_own_v4()[i].get_name() == "VecOwnerV4" + std::to_string(i));
        assert(new_pet.get_vec_own_v4()[i].get_age() == 220 + i);
    }

    std::cout << "\n\u2713 All basic tests passed!\n";
    return 0;
} 