cmake_minimum_required(VERSION 3.5.1)

project(client)

SET( SOURCES Client.cpp )
SET( HEADERS Client.h )
add_custom_command(
      OUTPUT "${hw_proto_srcs}" "${hw_proto_hdrs}" "${hw_grpc_srcs}" "${hw_grpc_hdrs}"
      COMMAND ${_PROTOBUF_PROTOC}
      ARGS --grpc_out "${CMAKE_BINARY_DIR}/protos"
        --cpp_out "${CMAKE_BINARY_DIR}/protos"
        -I "${hw_proto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${hw_proto}"
      DEPENDS "${hw_proto}")

include_directories(${CMAKE_BINARY_DIR}/protos)
add_executable(client ${SOURCES} ${SOURCES}
${hw_proto_srcs}
${hw_grpc_srcs})

target_link_libraries(client
${_REFLECTION}
${_GRPC_GRPCPP}
${_PROTOBUF_LIBPROTOBUF})
