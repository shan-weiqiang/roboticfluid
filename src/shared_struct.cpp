#include <sstream>
#include <string>
#include <cstring>
#include "shared_struct.hpp"

// Helper to write a length-prefixed string
static void write_string(std::ostream& os, const std::string& s) {
    uint32_t len = static_cast<uint32_t>(s.size());
    os.write(reinterpret_cast<const char*>(&len), sizeof(len));
    os.write(s.data(), len);
}

// Helper to read a length-prefixed string
static void read_string(std::istream& is, std::string& s) {
    uint32_t len = 0;
    is.read(reinterpret_cast<char*>(&len), sizeof(len));
    s.resize(len);
    if (len > 0) is.read(&s[0], len);
}

std::string Pet::serialize() const {
    std::ostringstream oss(std::ios::binary);
    write_string(oss, name);
    oss.write(reinterpret_cast<const char*>(&age), sizeof(age));
    oss.write(reinterpret_cast<const char*>(&weight), sizeof(weight));
    return oss.str();
}

void Pet::deserialize(const std::string& src) {
    std::istringstream iss(src, std::ios::binary);
    read_string(iss, name);
    iss.read(reinterpret_cast<char*>(&age), sizeof(age));
    iss.read(reinterpret_cast<char*>(&weight), sizeof(weight));
} 