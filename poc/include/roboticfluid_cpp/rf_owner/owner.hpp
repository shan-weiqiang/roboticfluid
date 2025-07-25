#pragma once

#include <string>

namespace rf_owner {

// Custom Owner class
class Owner {
public:
  // Data members (public)
  std::string name;
  int age;

  // Getters and Setters
  std::string get_name() const { return name; }
  void set_name(const std::string &val) { name = val; }
  int get_age() const { return age; }
  void set_age(int val) { age = val; }

  // Serialization
  std::string freeze() const;
  size_t melt(const std::string& src);
};

} // namespace rf_owner 