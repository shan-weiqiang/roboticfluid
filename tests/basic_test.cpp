#include <iostream>
#include <cassert>
#include <vector>
#include <string>
#include <array>
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
    Pet pet;
    pet.set_s("Buddy");
    pet.set_i32(5);
    pet.set_f(25.5);
    pet.set_d(45.2);
    pet.set_own(owner);

    // Set some arrays and vectors
    pet.set_arr_d({1.1, 2.2});
    pet.set_arr_f({3.3f, 4.4f});
    pet.set_arr_i32({10, 20});
    pet.set_arr_i64({100, 200});
    pet.set_arr_u32({1000, 2000});
    pet.set_arr_u64({10000, 20000});
    pet.set_arr_bval({true, false});
    pet.set_arr_s({"a", "b"});
    pet.set_vec_d({5.5, 6.6, 7.7});
    pet.set_vec_f({8.8f, 9.9f});
    pet.set_vec_i32({30, 40, 50});
    pet.set_vec_i64({300, 400});
    pet.set_vec_u32({3000, 4000});
    pet.set_vec_u64({30000, 40000});
    pet.set_vec_bval({false, true, true});
    pet.set_vec_s({"x", "y", "z"});

    // Set arr_u8
    std::array<uint8_t, 100> arr_u8;
    for (int i = 0; i < 100; ++i) arr_u8[i] = static_cast<uint8_t>(i);
    pet.set_arr_u8(arr_u8);
    std::cout << "Pet arr_u8: [";
    for (int i = 0; i < 10; ++i) std::cout << int(pet.get_arr_u8()[i]) << (i < 9 ? ", " : "");
    std::cout << "] ... (len=" << pet.get_arr_u8().size() << ")\n";

    std::cout << "Created pet: " << pet.get_s() << " (age: " << pet.get_i32() << ", weight: " << pet.get_f() << ")\n";
    std::cout << "Pet owner: " << pet.get_own().get_name() << "\n";
    std::cout << "Pet tricks: ";
    for (const auto& s : pet.get_vec_s()) std::cout << s << " ";
    std::cout << "\nPet favorite numbers: ";
    for (const auto& n : pet.get_arr_i32()) std::cout << n << " ";
    std::cout << "\n";

    // Test enum functionality
    pet.set_pet_type(PetType::DOG);
    pet.set_arr_pet_type({PetType::CAT, PetType::BIRD});
    pet.set_vec_pet_type({PetType::FISH, PetType::HAMSTER, PetType::RABBIT});
    std::cout << "Pet type: " << int(pet.get_pet_type()) << "\n";
    std::cout << "Pet type array: [" << int(pet.get_arr_pet_type()[0]) << ", " << int(pet.get_arr_pet_type()[1]) << "]\n";
    std::cout << "Pet type vector: ";
    for (auto t : pet.get_vec_pet_type()) std::cout << int(t) << " ";
    std::cout << "\n";

    // Test the bark method
    std::cout << "\nTesting bark method:\n";
    pet.bark();

    // Test freezing
    std::cout << "\n=== Testing freezing ===\n";
    std::string freezed = pet.freeze();
    std::cout << "Freezed pet: ";
    for (size_t i = 0; i < std::min<size_t>(16, freezed.size()); ++i)
        std::cout << std::hex << (unsigned int)(unsigned char)freezed[i] << " ";
    std::cout << "... (type: std::string, size: " << std::dec << freezed.size() << ")\n";

    // Test melting
    std::cout << "\n=== Testing melting ===\n";
    Pet new_pet;
    new_pet.melt(freezed);
    new_pet.melt(freezed);

    std::cout << "Melted s: " << new_pet.get_s() << "\n";
    std::cout << "Melted i32: " << new_pet.get_i32() << "\n";
    std::cout << "Melted arr_u8[:10]: [";
    for (int i = 0; i < 10; ++i) std::cout << int(new_pet.get_arr_u8()[i]) << (i < 9 ? ", " : "");
    std::cout << "]\n";
    for (int i = 0; i < 100; ++i) assert(new_pet.get_arr_u8()[i] == i);

    std::cout << "\n=== Testing round-trip freezing/melting ===\n";
    pet.set_s("Fido");
    pet.set_i32(42);
    pet.set_f(12.5);

    freezed = pet.freeze();
    std::cout << "Freezed: " << freezed.substr(0, 16) << "...\n";
    Pet p;
    p.melt(freezed);
    std::cout << "Melted s: " << p.get_s() << "\n";
    std::cout << "Melted i32: " << p.get_i32() << "\n";
    std::cout << "Melted f: " << p.get_f() << "\n";

    assert(p.get_s() == pet.get_s());
    assert(p.get_i32() == pet.get_i32());
    assert(std::abs(p.get_f() - pet.get_f()) < 1e-6);
    std::cout << "\u2713 Round-trip test passed!\n";

    std::cout << "\n\u2713 All basic tests passed!\n";
    return 0;
} 