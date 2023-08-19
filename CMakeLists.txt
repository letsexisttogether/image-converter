cmake_minimum_required(VERSION 3.18)

project(ImageConverter)

# Compiler preferencies
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")

# Source files
set(ImageFormat "ImageFormats/ImageFormat.cpp")
set(PPMFormat "ImageFormats/PPM/PPM.cpp")
set(Reader "ImageReaders/BMP/BMPReader.cpp")
set(Reader8 "ImageReaders/BMP/BMPPixelParsers/BMP8PixelParser/BMP8PixelParser.cpp")
set(Reader32 "ImageReaders/BMP/BMPPixelParsers/BMP32PixelParser/BMP32PixelParser.cpp")
set(Writer "ImageWriters/PPMWriter/PPMWriter.cpp")
set(ParsersFabric "ImageReaders/BMP/BMPParsersFabric/BMPParsersFabric.cpp")
set(Preparator "ImagePreparators/PPM/PPMPreparator.cpp")
set(Extra "Extra/PixelExtra.cpp")

set(SOURCES Main.cpp ${ImageFormat} ${PPMFormat} ${Reader} ${Reader8} 
    ${Reader32} ${Preparator} ${ParsersFabric} ${Writer} ${Extra}) 

add_executable(${PROJECT_NAME}
    ${SOURCES}) 

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}) 

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out)

