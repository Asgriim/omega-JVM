file(GLOB sources ./*.cpp)


foreach(X IN LISTS sources)
    string(REGEX MATCH "[^/]*\\.cpp"  OUT ${X})
    message(${OUT})
    target_sources(${EXEC_NAME} PRIVATE ${OUT})
endforeach()


target_include_directories(${EXEC_NAME} PRIVATE ${INCLUDE_DIR}/parser)
