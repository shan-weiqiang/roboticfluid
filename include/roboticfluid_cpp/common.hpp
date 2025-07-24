#pragma once
#include <string>
#include <cstdint>
#include <cstring>

namespace rf_common {

// Helper to write a length-prefixed string
inline void write_string(std::string &out, const std::string &s) {
    uint32_t len = static_cast<uint32_t>(s.size());
    out.append(reinterpret_cast<const char *>(&len), sizeof(len));
    out.append(s.data(), len);
}

// Helper to read a length-prefixed string
inline void read_string(const std::string &src, size_t &offset, std::string &s) {
    uint32_t len = 0;
    std::memcpy(&len, &src[offset], sizeof(len));
    offset += sizeof(len);
    s.assign(&src[offset], len);
    offset += len;
}

} // namespace rf_common 