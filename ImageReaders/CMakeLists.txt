include("${CMAKE_SOURCE_DIR}/CMakeModules/CreateReader.cmake")

set(EXTRAS "${CMAKE_SOURCE_DIR}/Extra/PixelExtra.cpp"
    "${CMAKE_SOURCE_DIR}/ImageFormats/ImageFormat.cpp")

CreateReader(PPM "P3;P6" "${EXTRAS}")
CreateReader(BMP "BMP8;BMP32" "${EXTRAS}")

