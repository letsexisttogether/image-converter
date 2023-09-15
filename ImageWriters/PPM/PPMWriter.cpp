#include "PPMWriter.hpp"

PPMWriter::PPMWriter(std::ofstream&& fileWriter, const PPM& image, Fabric&& fabric)
    : ImageWriterRealization<PPM>{ std::forward<std::ofstream>(fileWriter), image },
        m_Fabric{ fabric }
{}

void PPMWriter::WriteHeader() noexcept(false)
{
    m_FileWriter << m_Image.Format << '\n'
        << m_Image.Width << ' ' << m_Image.Height << '\n' 
        << m_Image.PixelMaxValue << '\n';
}

void PPMWriter::WriteData() noexcept(false)
{
    const auto& [height, width] = m_Image.GetResolution();

    for (ImageFormat::ScreenResolution h = 0; h < height; ++h)
    {
        std::unique_ptr<PPMDataCoder> coder
            { m_Fabric.SpawnObject(m_Image.Format, m_FileWriter, m_Image) };

        for (ImageFormat::ScreenResolution w = 0; w < width; ++w)
        {
            coder->CodeData(m_Image.GetPixel(h, w));
        }
    }   
}
