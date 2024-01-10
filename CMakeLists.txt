cmake_minimum_required(VERSION 3.25)

SET(VCPKG_PATH ~/vcpkg/vcpkg)

IF (NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    message(not found)
    SET(CMAKE_TOOLCHAIN_FILE ${VCPKG_PATH}/scripts/buildsystems/vcpkg.cmake)
ENDIF ()


project(omega_jvm)

include(FetchContent)


SET(TESTS_LIST "")
file(GLOB TESTS ./tests/*.cpp)

set(CMAKE_CXX_STANDARD 20)

set(EXEC_NAME omega-jvm)

set(ROOT_DIR ${CMAKE_SOURCE_DIR})

set(INCLUDE_DIR ${ROOT_DIR}/include)

message(${ROOT_DIR})
message(${INCLUDE_DIR})

include_directories(${INCLUDE_DIR})

add_executable(${EXEC_NAME} main.cpp)

add_subdirectory(src)
add_subdirectory(tests)

find_package(libzip QUIET)
if(NOT libzip_FOUND)
    FetchContent_Declare(libzip
            GIT_REPOSITORY https://github.com/nih-at/libzip
            GIT_TAG origin/main) # or whatever tag you want
    FetchContent_GetProperties(libzip)
    if(NOT libzip_POPULATED)
        FetchContent_Populate(libzip)
        add_subdirectory(${libzip_SOURCE_DIR} ${libzip_BINARY_DIR} EXCLUDE_FROM_ALL)
    endif()
endif()

target_link_libraries(${EXEC_NAME} PRIVATE libzip::zip)




