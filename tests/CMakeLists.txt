project(omega_jvm)

file(GLOB TESTS ./*.cpp)
file(GLOB_RECURSE SRC_FILES "../src/*.cpp")
file(GLOB_RECURSE HEADER_FILE ${INCLUDE_DIR}/*.h)

#include_directories(${INCLUDE_DIR})

foreach(X IN LISTS TESTS)
    string(REGEX MATCH "[^/]*\\.cpp"  OUT ${X})
    message(${OUT})
    add_executable(${OUT} ${OUT} ${SRC_FILES} ${HEADER_FILE})
endforeach()



