#pragma once

#include <string>

class OwnerV4 {
public:
  // Data members (public)
  std::string name;
  int age;

  // Getters and Setters
  std::string get_name() const { return name; }
  void set_name(const std::string &val) { name = val; }
  int get_age() const { return age; }
  void set_age(int val) { age = val; }
  std::string dump() const;
  size_t load(const std::string& src);
}; 