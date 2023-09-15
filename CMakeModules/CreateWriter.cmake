function(CreateWriter WRITER_NAME FORMATS EXTRAS)
    set(LIB_NAME ${WRITER_NAME}Writer)

    set(SOURCES "${WRITER_NAME}Writer.cpp")

    foreach(CODER IN LISTS FORMATS)
        list(APPEND SOURCES "DataCoders/${CODER}/${CODER}DataCoder.cpp")
    endforeach()

    list(TRANSFORM SOURCES PREPEND "${WRITER_NAME}/")

    foreach(EXTRA IN LISTS EXTRAS)
        list(APPEND SOURCES ${EXTRA})
    endforeach()

    add_library(${LIB_NAME} SHARED ${SOURCES})

    target_include_directories(${LIB_NAME} PRIVATE ${CMAKE_SOURCE_DIR})

    set_target_properties(${LIB_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY 
        ${CMAKE_BINARY_DIR}/ImageWriters)

endfunction()
