include("${CMAKE_SOURCE_DIR}/CMakeModules/CreateWriter.cmake")

set(EXTRAS "${CMAKE_SOURCE_DIR}/Extra/PixelExtra.cpp"
    "${CMAKE_SOURCE_DIR}/ImageFormats/ImageFormat.cpp")

CreateWriter(PPM "P3;P6" "${EXTRAS}")
