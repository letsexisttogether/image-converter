set(LIB_NAME PPMReader)

set(SOURCES 
    "${CMAKE_SOURCE_DIR}/ImageFormats/ImageFormat.cpp" 
    "${CMAKE_SOURCE_DIR}/Extra/PixelExtra.cpp"
    "PPMReader.cpp" 
    "DataParsers/P3/P3DataParser.cpp" 
    "DataParsers/P6/P6DataParser.cpp")

add_library(${LIB_NAME} SHARED ${SOURCES})

target_include_directories(${LIB_NAME} PRIVATE ${CMAKE_SOURCE_DIR})

set_target_properties(${LIB_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY 
    ${CMAKE_BINARY_DIR}/ImageReaders)

