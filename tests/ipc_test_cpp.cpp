#include <iostream>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <cstring>
#include "../include/shared_struct.hpp"

constexpr const char* SHM_NAME = "/roboticfluid_shm";
constexpr size_t SHM_SIZE = sizeof(SharedStruct);

int main() {
    int fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (fd == -1) {
        perror("shm_open");
        return 1;
    }
    ftruncate(fd, SHM_SIZE);
    void* ptr = mmap(nullptr, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap");
        return 1;
    }
    auto* data = reinterpret_cast<SharedStruct*>(ptr);

    // Write to fields
    data->set_d(3.14);
    data->set_f(2.71f);
    data->set_i32(42);
    data->set_i64(123456789);
    data->set_u32(100);
    data->set_u64(999999999);
    data->set_bval(true);
    data->set_s("hello from C++");
    // Print fields
    std::cout << "d: " << data->get_d() << std::endl;
    std::cout << "f: " << data->get_f() << std::endl;
    std::cout << "i32: " << data->get_i32() << std::endl;
    std::cout << "i64: " << data->get_i64() << std::endl;
    std::cout << "u32: " << data->get_u32() << std::endl;
    std::cout << "u64: " << data->get_u64() << std::endl;
    std::cout << "bval: " << data->get_bval() << std::endl;
    std::cout << "s: " << data->get_s() << std::endl;
    // Clean up
    munmap(ptr, SHM_SIZE);
    close(fd);
    return 0;
} 