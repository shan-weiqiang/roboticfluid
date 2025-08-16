#include <iostream>
#include <vector>
#include <chrono>
#include "../include/roboticfluid_cpp/rf_pet/pet.hpp"
#include "../include/roboticfluid_cpp/common.hpp"

using namespace rf_pet;

void test_compression() {
    std::cout << "=== Testing LZ4 Compression ===" << std::endl;
    
    // Create a Pet object with some data
    Pet pet;
    pet.set_d(3.14159);
    pet.set_f(2.71828f);
    pet.set_i32(42);
    pet.set_s("Hello, World!");
    
    // Fill arrays with some data
    std::array<double, 10000> arr_d;
    arr_d.fill(1.234);
    pet.set_arr_d(arr_d);
    
    std::array<std::string, 10000> arr_s;
    arr_s.fill("test_string");
    pet.set_arr_s(arr_s);
    
    // Test regular serialization
    std::vector<uint8_t> uncompressed;
    auto start = std::chrono::high_resolution_clock::now();
    pet.dump(uncompressed);
    auto end = std::chrono::high_resolution_clock::now();
    auto serialize_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "Uncompressed size: " << uncompressed.size() << " bytes" << std::endl;
    std::cout << "Serialization time: " << serialize_time.count() << " μs" << std::endl;
    
    // Test compressed serialization
    start = std::chrono::high_resolution_clock::now();
    std::vector<uint8_t> compressed;
    compressed.reserve(20 * 1024 * 1024); // 20MB
    pet.dump_compressed(compressed);
    end = std::chrono::high_resolution_clock::now();
    auto compress_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "Compressed size: " << compressed.size() << " bytes" << std::endl;
    std::cout << "Compression time: " << compress_time.count() << " μs" << std::endl;
    
    // Calculate compression ratio
    double compression_ratio = (1.0 - static_cast<double>(compressed.size()) / uncompressed.size()) * 100.0;
    std::cout << "Compression ratio: " << compression_ratio << "%" << std::endl;
    
    // Test decompression
    Pet pet2;
    start = std::chrono::high_resolution_clock::now();
    bool success = pet2.load_compressed(compressed);
    end = std::chrono::high_resolution_clock::now();
    auto decompress_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    if (success) {
        std::cout << "Decompression successful!" << std::endl;
        std::cout << "Decompression time: " << decompress_time.count() << " μs" << std::endl;
        
        // Verify data integrity
        if (pet.get_d() == pet2.get_d() && 
            pet.get_f() == pet2.get_f() && 
            pet.get_i32() == pet2.get_i32() && 
            pet.get_s() == pet2.get_s()) {
            std::cout << "Data integrity verified!" << std::endl;
        } else {
            std::cout << "Data integrity check failed!" << std::endl;
        }
    } else {
        std::cout << "Decompression failed!" << std::endl;
    }
    
    std::cout << std::endl;
}

int main() {
    test_compression();
    return 0;
} 