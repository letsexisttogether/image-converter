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
set(PPMReader "ImageReaders/PPMReader/PPMReader.cpp")
set(PPMP6Reader "ImageReaders/PPMReader/PPMP6Reader.cpp")
set(PPMWriter "ImageWriters/PPMWriter/PPMWriter.cpp")
set(Pixel "Pixel/Pixel.cpp")

set(SOURCES Main.cpp ${ImageFormat} ${PPMFormat} ${PPMReader} ${PPMP6Reader} ${PPMWriter} ${Pixel})

add_executable(${PROJECT_NAME}
    ${SOURCES}) 

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}) 

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out)

