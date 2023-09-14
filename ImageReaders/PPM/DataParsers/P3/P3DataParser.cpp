#include "P3DataParser.hpp"

Pixel P3DataParser::ReadPixel(std::ifstream& fileReader) noexcept
{
    Pixel pixel{};
    
    fileReader >> pixel.Red >> pixel.Green >> pixel.Blue;

    return pixel;
}
