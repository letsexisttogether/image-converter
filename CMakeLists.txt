cmake_minimum_required(VERSION 3.18)

project(ImageConverter)

# Compiler preferencies
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")

# Windows preferences
set(CMAKE_CXX_FLAGS "-m64")
add_definitions(-D_WIN64)

set(SOURCES Main.cpp "ImageFormats/ImageFormat.cpp") 

add_executable(${PROJECT_NAME}
    ${SOURCES}) 

add_subdirectory(ImageReaders)
add_subdirectory(ImageWriters)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}) 

target_link_libraries(${PROJECT_NAME} PRIVATE kernel32)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out)

