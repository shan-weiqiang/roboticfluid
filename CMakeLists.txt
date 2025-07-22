cmake_minimum_required(VERSION 3.14)
project(roboticfluid LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Fetch pybind11 from GitHub
include(FetchContent)
FetchContent_Declare(
    pybind11
    GIT_REPOSITORY https://github.com/pybind/pybind11.git
    GIT_TAG v2.11.1
)
FetchContent_MakeAvailable(pybind11)

# Library target for C++
add_library(roboticfluid SHARED
    src/shared_struct.cpp
)
target_include_directories(roboticfluid PUBLIC include)

# Python module
pybind11_add_module(roboticfluid_python src/pybind_module.cpp)
target_include_directories(roboticfluid_python PRIVATE include)
target_link_libraries(roboticfluid_python PRIVATE roboticfluid)

# C++ IPC test executable
enable_testing()
add_executable(ipc_test_cpp tests/ipc_test_cpp.cpp)
target_include_directories(ipc_test_cpp PRIVATE include)
target_link_libraries(ipc_test_cpp PRIVATE roboticfluid rt)
set_target_properties(ipc_test_cpp PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests)

# Install rules
install(TARGETS roboticfluid DESTINATION lib)
install(DIRECTORY include/ DESTINATION include) 