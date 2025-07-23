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

std::string Pet::freeze() const {
    std::ostringstream oss(std::ios::binary);
    // Serialize main Pet fields
    write_string(oss, s);
    oss.write(reinterpret_cast<const char*>(&i32), sizeof(i32));
    oss.write(reinterpret_cast<const char*>(&f), sizeof(f));
    // Serialize own
    write_string(oss, own.name);
    oss.write(reinterpret_cast<const char*>(&own.age), sizeof(own.age));
    // Serialize arr_own
    for (const auto& o : arr_own) {
        write_string(oss, o.name);
        oss.write(reinterpret_cast<const char*>(&o.age), sizeof(o.age));
    }
    // Serialize vec_own
    uint32_t sz = static_cast<uint32_t>(vec_own.size());
    oss.write(reinterpret_cast<const char*>(&sz), sizeof(sz));
    for (const auto& o : vec_own) {
        write_string(oss, o.name);
        oss.write(reinterpret_cast<const char*>(&o.age), sizeof(o.age));
    }
    return oss.str();
}

void Pet::melt(const std::string& src) {
    std::istringstream iss(src, std::ios::binary);
    // Deserialize main Pet fields
    read_string(iss, s);
    iss.read(reinterpret_cast<char*>(&i32), sizeof(i32));
    iss.read(reinterpret_cast<char*>(&f), sizeof(f));
    // Deserialize own
    read_string(iss, own.name);
    iss.read(reinterpret_cast<char*>(&own.age), sizeof(own.age));
    // Deserialize arr_own
    for (auto& o : arr_own) {
        read_string(iss, o.name);
        iss.read(reinterpret_cast<char*>(&o.age), sizeof(o.age));
    }
    // Deserialize vec_own
    uint32_t sz = 0;
    iss.read(reinterpret_cast<char*>(&sz), sizeof(sz));
    vec_own.resize(sz);
    for (auto& o : vec_own) {
        read_string(iss, o.name);
        iss.read(reinterpret_cast<char*>(&o.age), sizeof(o.age));
    }
} 