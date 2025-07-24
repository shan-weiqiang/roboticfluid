#pragma once

#include <string>

namespace rf_owner {

class OwnerV2 {
public:
  // Data members (public)
  std::string name;
  int age;

  // Getters and Setters
  std::string get_name() const { return name; }
  void set_name(const std::string &val) { name = val; }
  int get_age() const { return age; }
  void set_age(int val) { age = val; }
};

} // namespace rf_owner 