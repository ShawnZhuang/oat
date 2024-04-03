cmake_minimum_required(VERSION 3.0.0)
project(oat VERSION 0.1.0)



add_subdirectory(3rdparty/tvm) 
file(GLOB_RECURSE COMPILER_SRCS src/*.cc)

message("src files are" ${COMPILER_SRCS})
# list(APPEND COMPILER_SRCS ${CODEGEN_SRCS})
set(CMAKE_CXX_FLAGS "-std=c++17 ${CMAKE_CXX_FLAGS}")
add_library(oat SHARED ${COMPILER_SRCS})
include_directories("include")
include_directories(SYSTEM "3rdparty/tvm/include/")
include_directories(SYSTEM "3rdparty/tvm/3rdparty/dmlc-core/include")
include_directories(SYSTEM "3rdparty/tvm/3rdparty/dlpack/include")
include_directories(SYSTEM "3rdparty/tvm/3rdparty/rang/include")

set_target_properties(oat PROPERTIES OUTPUT_NAME "oat")

find_package(Protobuf REQUIRED)

target_compile_definitions(oat PUBLIC)
# target_link_libraries(oat PUBLIC tvm)
target_link_libraries(oat PUBLIC tvm protobuf)
# set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

# include(CTest)
# enable_testing()
# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)
