cmake_minimum_required(VERSION 3.5.1)

# Use vcpkg
if(NOT VCPKG_ROOT)
  set(VCPKG_ROOT C:/dev/vcpkg)
  set(CMAKE_TOOLCHAIN_FILE ${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)
  set(VCPKG_TARGET_TRIPLET x64-windows)
endif()

project(grpc-push-reliability)

SET( CMAKE_VERBOSE_MAKEFILE on)

if(NOT MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
else()
  add_definitions(-D_WIN32_WINNT=0x600)
endif()

find_package(Threads REQUIRED)
set(protobuf_MODULE_COMPATIBLE TRUE)
find_package(Protobuf CONFIG REQUIRED)
message(STATUS "Using protobuf ${Protobuf_VERSION}")

set(_PROTOBUF_LIBPROTOBUF protobuf::libprotobuf)
set(_REFLECTION gRPC::grpc++_reflection)
if(CMAKE_CROSSCOMPILING)
find_program(_PROTOBUF_PROTOC protoc)
else()
set(_PROTOBUF_PROTOC $<TARGET_FILE:protobuf::protoc>)
endif()

# Find gRPC installation
# Looks for gRPCConfig.cmake file installed by gRPC's cmake installation.
find_package(gRPC CONFIG REQUIRED)
message(STATUS "Using gRPC ${gRPC_VERSION}")

set(_GRPC_GRPCPP gRPC::grpc++)
if(CMAKE_CROSSCOMPILING)
find_program(_GRPC_CPP_PLUGIN_EXECUTABLE grpc_cpp_plugin)
else()
set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:gRPC::grpc_cpp_plugin>)
endif()


# Proto file
get_filename_component(hw_proto "protos/notify.proto" ABSOLUTE)
get_filename_component(hw_proto_path "${hw_proto}" PATH)

# Generated sources
set(hw_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/protos/notify.pb.cc")
set(hw_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/protos/notify.pb.h")
set(hw_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/protos/notify.grpc.pb.cc")
set(hw_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/protos/notify.grpc.pb.h")

# Include generated *.pb.h files
include_directories("${CMAKE_CURRENT_BINARY_DIR}/protos/")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_subdirectory( client )
add_subdirectory( server )
