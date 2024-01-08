project(omega_jvm)

file(GLOB TESTS ./*.cpp)
file(GLOB_RECURSE SRC_FILES "../src/*.cpp")
file(GLOB_RECURSE HEADER_FILE ${INCLUDE_DIR}/*.h)

#include_directories(${INCLUDE_DIR})

foreach(X IN LISTS TESTS)
    string(REGEX MATCH "[^/]*\\.cpp"  OUT ${X})
    string(REPLACE ".cpp" "" EXEC ${OUT})
    message(${EXEC})
    add_executable(${EXEC} ${OUT} ${SRC_FILES} ${HEADER_FILE})
endforeach()



