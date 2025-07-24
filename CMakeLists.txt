cmake_minimum_required(VERSION 3.14)
project(roboticfluid LANGUAGES CXX)

# Set install prefix to build directory for testing
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/roboticfluid)

# Include GNU tools directory
include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_INSTALL_RPATH $ORIGIN/../)


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

# C++ Library target for roboticfluid types
add_library(roboticfluid_cpp SHARED
    src/roboticfluid_cpp/rf_pet/pet.cpp
)
target_include_directories(roboticfluid_cpp PUBLIC include)
set_target_properties(roboticfluid_cpp PROPERTIES
    OUTPUT_NAME "roboticfluid_cpp"
)

# Python module for roboticfluid.rf_owner
pybind11_add_module(roboticfluid_rf_owner
    src/roboticfluid_py/rf_owner.cpp
    src/roboticfluid_py/rf_owner/owner.cpp
    src/roboticfluid_py/rf_owner/owner_v2.cpp
    src/roboticfluid_py/rf_owner/nested.cpp
    src/roboticfluid_py/rf_owner/nested/owner_v3.cpp
)
target_include_directories(roboticfluid_rf_owner PRIVATE include)
target_link_libraries(roboticfluid_rf_owner PRIVATE roboticfluid_cpp)
set_target_properties(roboticfluid_rf_owner PROPERTIES
    PREFIX ""
    OUTPUT_NAME "rf_owner"
    SUFFIX "${PYTHON_EXT_SUFFIX}"
)

# Python module for roboticfluid.rf_pet
pybind11_add_module(roboticfluid_rf_pet
    src/roboticfluid_py/rf_pet.cpp
    src/roboticfluid_py/rf_pet/pet.cpp
    src/roboticfluid_py/rf_pet/pet_type.cpp
)
target_include_directories(roboticfluid_rf_pet PRIVATE include)
target_link_libraries(roboticfluid_rf_pet PRIVATE roboticfluid_cpp)
set_target_properties(roboticfluid_rf_pet PROPERTIES
    PREFIX ""
    OUTPUT_NAME "rf_pet"
    SUFFIX "${PYTHON_EXT_SUFFIX}"
)

# Python module for roboticfluid.owner_v4 (top-level)
pybind11_add_module(owner_v4 src/roboticfluid_py/owner_v4.cpp)
target_include_directories(owner_v4 PRIVATE include)
target_link_libraries(owner_v4 PRIVATE roboticfluid_cpp)
set_target_properties(owner_v4 PROPERTIES
    PREFIX ""
    OUTPUT_NAME "owner_v4"
    SUFFIX "${PYTHON_EXT_SUFFIX}"
)

# Install rules
install(TARGETS roboticfluid_cpp DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(TARGETS roboticfluid_rf_owner roboticfluid_rf_pet owner_v4 DESTINATION ${CMAKE_INSTALL_LIBDIR}/roboticfluid_py)
install(DIRECTORY include/roboticfluid_cpp DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} FILES_MATCHING PATTERN "*.hpp")
install(DIRECTORY include/roboticfluid_py DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} FILES_MATCHING PATTERN "*.pyi")
install(FILES src/roboticfluid_py/__init__.py DESTINATION ${CMAKE_INSTALL_LIBDIR}/roboticfluid_py) 