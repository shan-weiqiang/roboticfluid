A fast serialization type system and it's compiler. This type system support both C++ and Python API, sharing the same memory underneath, avoiding conversion between C++ and Python. For data persistence, instead of traditional member-wise serialization/deserialization, this type system takes memory dump/load approach, which is intrinsically faster than conventional serialization methods. This is achieved through static memory analysis of data types during compile time and code generation, all by it's compiler. 

- [Architecture](#architecture)
- [Supported Types](#supported-types)
  - [Type Categories](#type-categories)
  - [Key Features](#key-features)
- [Benchmark](#benchmark)


# Architecture

![`roboticfluid` architecture](assets/roboticfluid.png)

# Supported Types

The roboticfluid type system supports a wide range of data types, from basic primitives to complex custom types, with both fixed-size arrays and dynamic arrays. All types share the same memory layout between C++ and Python, enabling zero-copy data exchange.

## Type Categories

| Category | C++ Type | Python Type | Fixed Array | Dynamic Array | Example |
|----------|----------|-------------|-------------|---------------|---------|
| **Basic Types** | | | | | |
| Integer (32-bit) | `int32_t` | `int` | `std::array<int32_t, N>` | `std::vector<int32_t>` | `123` |
| Integer (64-bit) | `int64_t` | `int` | `std::array<int64_t, N>` | `std::vector<int64_t>` | `1234567890123` |
| Unsigned (32-bit) | `uint32_t` | `int` | `std::array<uint32_t, N>` | `std::vector<uint32_t>` | `123456` |
| Unsigned (64-bit) | `uint64_t` | `int` | `std::array<uint64_t, N>` | `std::vector<uint64_t>` | `123456789012345` |
| Unsigned (8-bit) | `uint8_t` | `int` | `std::array<uint8_t, N>` | `std::vector<uint8_t>` | `255` |
| Float (32-bit) | `float` | `float` | `std::array<float, N>` | `std::vector<float>` | `3.14` |
| Float (64-bit) | `double` | `float` | `std::array<double, N>` | `std::vector<double>` | `3.14159265359` |
| Boolean | `bool` | `bool` | `std::array<bool, N>` | `std::vector<bool>` | `True` |
| String | `std::string` | `str` | `std::array<std::string, N>` | `std::vector<std::string>` | `"Hello World"` |
| **Enum Types** | | | | | |
| Enum | `enum class` | `Enum` | `std::array<Enum, N>` | `std::vector<Enum>` | `PetType.DOG` |
| **Custom Types** | | | | | |
| Custom Class | `class` | `Class` | `std::array<Class, N>` | `std::vector<Class>` | `Owner()` |

## Key Features

- **Zero-copy**: C++ and Python share the same memory layout
- **Memory dump/load**: Fast binary serialization without member-wise operations
- **Type safety**: Compile-time type checking and validation
- **Array support**: Both fixed-size (`std::array`) and dynamic (`std::vector`) arrays
- **Nested types**: Support for complex nested data structures


# Benchmark

![alt text](poc/benchmark/benchmark_performance_only.png)

*Note: The benchmark source code can be found in the [benchmark](poc/benchmark/) directory.*
