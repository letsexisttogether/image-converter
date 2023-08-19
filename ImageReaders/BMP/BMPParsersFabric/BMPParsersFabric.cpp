#include "BMPParsersFabric.hpp"

BMPParsersFabric::BMPParsersFabric(const BMPParsersFabric::FunctionsMap& map)
    : m_Functions{ map }
{}

BMPParsersFabric::BMPParsersFabric(BMPParsersFabric::FunctionsMap&& map)
    : m_Functions{ std::move(map) }
{}

// TODO: Get out of exceptions
BMPPixelParser* BMPParsersFabric::GetBMPParser(const BMP& bmp) noexcept(false)
{
    const auto& iter = m_Functions.find(bmp.BitsPerPixel);

    if (iter == m_Functions.end())
    {
        throw std::runtime_error{ "DEV: wrong format" };
    }

    return iter->second(bmp);
}

bool BMPParsersFabric::CheckBPPExistance(const BMP::BPPType bpp) const noexcept
{
    return (m_Functions.find(bpp) != m_Functions.end());
}
