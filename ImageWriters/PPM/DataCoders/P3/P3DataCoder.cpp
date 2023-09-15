#include "P3DataCoder.hpp"

P3DataCoder::P3DataCoder(std::ofstream& fileWriter)
    : PPMDataCoder{ fileWriter }
{}

P3DataCoder::~P3DataCoder()
{
    m_FileWriter << '\n';
}

void P3DataCoder::CodeData(const Pixel& pixel) noexcept
{
    m_FileWriter << pixel.Red << ' ' << pixel.Green << ' ' << pixel.Blue;
}
