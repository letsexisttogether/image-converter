#include "P3DataParser.hpp"

P3DataParser::P3DataParser(std::ifstream& m_FileReader)
    : PPMDataParser{ m_FileReader }
{}

Pixel P3DataParser::ReadPixel() noexcept
{
    Pixel pixel{};
    
    m_FileReader >> pixel.Red >> pixel.Green >> pixel.Blue;

    return pixel;
}
