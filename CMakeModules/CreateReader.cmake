function(CreateReader READER_NAME FORMATS EXTRAS)
    set(LIB_NAME ${READER_NAME}Reader)

    set(SOURCES "${READER_NAME}Reader.cpp")

    foreach(PARSER IN LISTS FORMATS)
        list(APPEND SOURCES "DataParsers/${PARSER}/${PARSER}DataParser.cpp")
    endforeach()

    list(TRANSFORM SOURCES PREPEND "${READER_NAME}/")

    foreach(EXTRA IN LISTS EXTRAS)
        list(APPEND SOURCES ${EXTRA})
    endforeach()

    add_library(${LIB_NAME} SHARED ${SOURCES})

    target_include_directories(${LIB_NAME} PRIVATE ${CMAKE_SOURCE_DIR})

    set_target_properties(${LIB_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY 
        ${CMAKE_BINARY_DIR}/ImageReaders)

endfunction()
