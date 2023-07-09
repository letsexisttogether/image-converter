cmake_minimum_required(VERSION 3.18)

project(ImageConverter)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")

# Source files 
set(FileReaderSrc FileReader/FileReader.cpp)
set(ImageReaderSrc ImageReaders/ImageReader.cpp)

add_executable(${PROJECT_NAME}
    Main.cpp ${FileReaderSrc} ${ImageReaderSrc})
    
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIRECTORY})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out)
