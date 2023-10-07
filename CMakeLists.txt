cmake_minimum_required(VERSION 3.26)
project(omega_jvm)

SET(TESTS_LIST "")
file(GLOB TESTS ./tests/*.cpp)


foreach(X IN LISTS TESTS)
    string(REGEX MATCH "[^/]*\\.cpp"  OUT ${X})
    LIST(APPEND TESTS_LIST ${OUT})
    add_executable(${OUT} tests/${OUT})
endforeach()


set(CMAKE_CXX_STANDARD 20)

set(EXEC_NAME omega-jvm)

set(ROOT_DIR ${CMAKE_SOURCE_DIR})

set(INCLUDE_DIR ${ROOT_DIR}/include)

message(${ROOT_DIR})
message(${INCLUDE_DIR})
include_directories(${INCLUDE_DIR})

add_executable(${EXEC_NAME} main.cpp)

add_subdirectory(src/parser)
add_subdirectory(src/classfile)
add_subdirectory(tests)
add_subdirectory(src/util)