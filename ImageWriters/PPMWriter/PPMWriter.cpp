#include "PPMWriter.hpp"

PPMWriter::PPMWriter(std::ofstream&& fileWriter, const PPM& image)
    : ImageWriterRealization<PPM>{ std::forward<std::ofstream>(fileWriter), image }
{}

void PPMWriter::WriteHeader() noexcept(false)
{
    m_FileWriter << m_Image.GetFormat() << '\n'
        << m_Image.GetWidth() << ' ' << m_Image.GetHeight() << ' ' 
        << m_Image.GetPixelMaxValue() << '\n';
}

void PPMWriter::WriteData() noexcept(false)
{
    const auto& [height, width] = m_Image.GetResolution();

    for (ImageFormat::ScreenResolution h = 0; h < height; ++h)
    {
        for (ImageFormat::ScreenResolution w = 0; w < width; ++w)
        {
            const auto& [r, g, b] = m_Image.GetPixel(h, w).GetColorValues(); 

            m_FileWriter << r << ' ' << g << ' ' << b << ' ';
        }

        m_FileWriter << '\n';
    }   
}
