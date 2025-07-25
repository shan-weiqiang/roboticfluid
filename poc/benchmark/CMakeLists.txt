cmake_minimum_required(VERSION 3.10)
project(pet_benchmark)

set(CMAKE_CXX_STANDARD 17)
include(GNUInstallDirs)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -O2")
set(protobuf_SRC "../bin/protobuf-src")
list(PREPEND CMAKE_PREFIX_PATH "${protobuf_SRC}/lib/cmake/protobuf")
set(protobuf_INCLUDE "${protobuf_SRC}/include")
set(protobuf_LIBDIR "${protobuf_SRC}/lib")
find_package(protobuf REQUIRED)

# Protobuf code generation
set(PROTO_FILE ${CMAKE_CURRENT_SOURCE_DIR}/pet.proto)
execute_process(
    COMMAND ${protobuf_SRC}/bin/protoc --proto_path . pet.proto --cpp_out .
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
    RESULT_VARIABLE result
    OUTPUT_VARIABLE variable
    )

set(FastDDS_PREFIX "${CMAKE_CURRENT_LIST_DIR}/../bin/fastdds_v2.11.3")
list(PREPEND CMAKE_PREFIX_PATH "${FastDDS_PREFIX}/share/fastrtps/cmake")
list(PREPEND CMAKE_PREFIX_PATH "${FastDDS_PREFIX}/lib/cmake/fastcdr")
list(PREPEND CMAKE_PREFIX_PATH "${FastDDS_PREFIX}/lib/foonathan_memory/cmake")
find_package(fastrtps REQUIRED)
find_package(fastcdr REQUIRED)
find_package(foonathan_memory REQUIRED)
include(cmake/fastdds-generate.cmake)


set(IDL_FILE ${CMAKE_CURRENT_SOURCE_DIR}/pet.idl)

fastdds_generate(
    CXX_OUT_VAR SRCS
    HPP_OUT_VAR HDRS
    IDLS ${IDL_FILE}
    OUT_DIR ${CMAKE_CURRENT_LIST_DIR}
    IMPORT_DIRS ${CMAKE_CURRENT_LIST_DIR}
)

# nanobench
include_directories(${CMAKE_SOURCE_DIR}/thirdparty)

# Custom include and src
include_directories(${CMAKE_SOURCE_DIR}/../include)

# Add executable and link libraries
add_executable(pet_benchmark main.cpp ${SRCS}
    ../src/roboticfluid_cpp/rf_pet/pet.cpp
    ../src/roboticfluid_cpp/rf_owner/owner.cpp
    ../src/roboticfluid_cpp/rf_owner/owner_v2.cpp
    ../src/roboticfluid_cpp/rf_owner/nested/owner_v3.cpp
    ../src/roboticfluid_cpp/owner_v4.cpp
    pet.pb.cc
)

target_link_libraries(pet_benchmark
    PRIVATE
        protobuf::libprotobuf
        fastrtps
        fastcdr
        foonathan_memory
)

