cmake_minimum_required(VERSION 3.0.0)
project(oat_test VERSION 0.1.0)

message("The cpp test cmake home is: ${CMAKE_HOME_DIRECTORY}")

include(${CMAKE_HOME_DIRECTORY}/../../cmake/inc.cmake)
# target_include_directories()(../cmake/inc.cmake)
 # add_subdirectory(3rdparty/tvm) 

# find_package(GMock REQUIRED)

file(GLOB_RECURSE COMPILER_SRCS onnx/*.cc)

message("src files are" ${COMPILER_SRCS})
# list(APPEND COMPILER_SRCS ${CODEGEN_SRCS})
set(CMAKE_CXX_FLAGS "-std=c++17 ${CMAKE_CXX_FLAGS}")
# add_library(oat_test SHARED ${COMPILER_SRCS})

add_executable(oat_test ${COMPILER_SRCS})

include_directories("${CMAKE_HOME_DIRECTORY}/../../include")
include_directories(SYSTEM "${CMAKE_HOME_DIRECTORY}/../../3rdparty/tvm/include/")
include_directories(SYSTEM "${CMAKE_HOME_DIRECTORY}/../../3rdparty/tvm/3rdparty/dmlc-core/include")
include_directories(SYSTEM "${CMAKE_HOME_DIRECTORY}/../../3rdparty/tvm/3rdparty/dlpack/include")
include_directories(SYSTEM "${CMAKE_HOME_DIRECTORY}/../../3rdparty/tvm/3rdparty/rang/include")

set_target_properties(oat_test PROPERTIES OUTPUT_NAME "oat_test")

target_compile_definitions(oat_test PUBLIC)

# target_link_libraries(subdir_target ${PROJECT_SOURCE_DIR}/../lib/my_library.a)

target_link_directories(oat_test PUBLIC 
"${CMAKE_HOME_DIRECTORY}/../../build" 
"${CMAKE_HOME_DIRECTORY}/../../build/3rdparty/tvm"
)
find_package(GTest REQUIRED)
target_link_libraries(oat_test  PUBLIC oat tvm tvm_runtime GTest::GTest GTest::Main)