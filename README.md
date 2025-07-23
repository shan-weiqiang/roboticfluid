# RoboticFluid IPC Example

This project demonstrates inter-process communication (IPC) between C++ and Python using shared memory and pybind11. The project uses `Pet` and `Owner` classes to showcase complex data structures that can be shared between processes.

## Structure

- `include/shared_struct.hpp`: Contains the `Pet` and `Owner` class definitions
- `src/shared_struct.cpp`: Implementation of serialization methods
- `src/pybind_module.cpp`: Python bindings using pybind11
- `tests/`: Test files for both C++ and Python
- `CMakeLists.txt`: Build configuration

## Classes

### Owner Class
Simple class with name and age:
```cpp
class Owner {
    std::string name_;
    int age_;
    // getters and setters
};
```

### Pet Class
Complex class with various data types:
```cpp
class Pet {
    std::string name;
    int age;
    float weight;
    double height;
    bool isVaccinated;
    char gender;
    std::array<int, 3> favoriteNumbers;
    std::array<float, 2> coordinates;
    std::vector<std::string> tricks;
    std::vector<int> scores;
    Owner owner;
    std::array<Owner, 2> multipleOwners;
    std::vector<Owner> ownerList;
    // methods including bark(), serialize(), deserialize()
};
```

## Building

```bash
mkdir build
cd build
cmake ..
make -j$(nproc)
```

## Running Tests

```bash
./run_tests.sh
```

This will:
1. Build the project
2. Run basic functionality tests
3. Run C++ IPC test (writes data to shared memory)
4. Run Python IPC test (reads and modifies data from shared memory)

## Usage

### Python
```python
from example import Pet, Owner

# Create objects
owner = Owner()
owner.name = "John"
owner.age = 30

pet = Pet()
pet.name = "Buddy"
pet.age = 5
pet.owner = owner

# Use methods
pet.bark()
serialized = pet.serialize()
```

### C++
```cpp
#include "shared_struct.hpp"

Owner owner;
owner.setName("John");
owner.setAge(30);

Pet pet;
pet.setName("Buddy");
pet.setAge(5);
pet.setOwner(owner);

pet.bark();
std::string serialized = pet.serialize();
```

## IPC Usage

The project demonstrates how to share `Pet` objects between C++ and Python processes using shared memory:

1. C++ process creates a `Pet` object in shared memory
2. Python process accesses the same memory location
3. Both processes can read and modify the same data

This is useful for high-performance inter-process communication where you need to share complex data structures.
