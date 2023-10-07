file(GLOB sources ./*.cpp)

set(DIR "classfile")

foreach(X IN LISTS sources)
    string(REGEX MATCH "[^/]*\\.cpp"  OUT ${X})
    message(${OUT})
    target_sources(${EXEC_NAME} PUBLIC ${OUT})

    foreach (Y ${TESTS_LIST})
        target_include_directories(${Y} PUBLIC ${INCLUDE_DIR}/${DIR})
        target_sources(${Y} PUBLIC ${OUT})
    endforeach ()

endforeach()

target_include_directories(${EXEC_NAME} PRIVATE ${INCLUDE_DIR}/${DIR})
