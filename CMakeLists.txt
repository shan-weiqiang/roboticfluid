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

# Detect Python version for extension suffix
execute_process(
    COMMAND ${PYTHON_EXECUTABLE} -c "import sys; print(f'{sys.version_info.major} {sys.version_info.minor}')"
    RESULT_VARIABLE _PYTHON_VERSION_RESULT
    OUTPUT_VARIABLE _PYTHON_VERSION_OUTPUT
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
string(REPLACE " " ";" _PYTHON_VERSION_LIST "${_PYTHON_VERSION_OUTPUT}")
list(GET _PYTHON_VERSION_LIST 0 PYTHON_VERSION_MAJOR)
list(GET _PYTHON_VERSION_LIST 1 PYTHON_VERSION_MINOR)

# Detect Python extension suffix for platform and version
execute_process(
    COMMAND ${PYTHON_EXECUTABLE} -c "from sysconfig import get_config_var; print(get_config_var('EXT_SUFFIX'))"
    OUTPUT_VARIABLE PYTHON_EXT_SUFFIX
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Library target for C++
add_library(roboticfluid SHARED
    src/shared_struct.cpp
)
target_include_directories(roboticfluid PUBLIC include)

# Python module for roboticfluid.rf_owner
pybind11_add_module(roboticfluid_rf_owner
    src/roboticfluid/rf_owner/module.cpp
    src/roboticfluid/rf_owner/owner.cpp
    src/roboticfluid/rf_owner/owner_v2.cpp
    src/roboticfluid/rf_owner/nested.cpp
    src/roboticfluid/rf_owner/nested/owner_v3.cpp
)
target_include_directories(roboticfluid_rf_owner PRIVATE include)
target_link_libraries(roboticfluid_rf_owner PRIVATE roboticfluid)
set_target_properties(roboticfluid_rf_owner PROPERTIES
    PREFIX ""
    OUTPUT_NAME "rf_owner"
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/roboticfluid
    SUFFIX "${PYTHON_EXT_SUFFIX}"
)

# Python module for roboticfluid.rf_pet
pybind11_add_module(roboticfluid_rf_pet
    src/roboticfluid/rf_pet/module.cpp
    src/roboticfluid/rf_pet/pet.cpp
)
target_include_directories(roboticfluid_rf_pet PRIVATE include)
target_link_libraries(roboticfluid_rf_pet PRIVATE roboticfluid)
set_target_properties(roboticfluid_rf_pet PROPERTIES
    PREFIX ""
    OUTPUT_NAME "rf_pet"
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/roboticfluid
    SUFFIX "${PYTHON_EXT_SUFFIX}"
)

# Python module for roboticfluid.owner_v4 (top-level)
pybind11_add_module(owner_v4 src/roboticfluid/owner_v4.cpp)
target_include_directories(owner_v4 PRIVATE include)
set_target_properties(owner_v4 PROPERTIES
    PREFIX ""
    OUTPUT_NAME "owner_v4"
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/roboticfluid
    SUFFIX "${PYTHON_EXT_SUFFIX}"
)

# Ensure __init__.py is present in the build/roboticfluid directory
configure_file(src/roboticfluid/__init__.py ${CMAKE_BINARY_DIR}/roboticfluid/__init__.py COPYONLY)

# Install rules
install(TARGETS roboticfluid DESTINATION lib)
install(DIRECTORY include/ DESTINATION include)
install(FILES src/roboticfluid/__init__.py DESTINATION roboticfluid)

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/roboticfluid) 