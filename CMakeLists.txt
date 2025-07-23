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

# Python module for rf_owner (structured in subfolder)
pybind11_add_module(rf_owner src/rf_owner/module.cpp src/rf_owner/owner.cpp src/rf_owner/owner_v2.cpp)
target_include_directories(rf_owner PRIVATE include)
target_link_libraries(rf_owner PRIVATE roboticfluid)

# Python module for rf_pet (structured in subfolder)
pybind11_add_module(rf_pet src/rf_pet/module.cpp src/rf_pet/pet.cpp)
target_include_directories(rf_pet PRIVATE include)
target_link_libraries(rf_pet PRIVATE roboticfluid)

# Install rules
install(TARGETS roboticfluid DESTINATION lib)
install(DIRECTORY include/ DESTINATION include) 