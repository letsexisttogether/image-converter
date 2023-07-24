#include "PPMP6Reader.hpp"

PPMP6Reader::PPMP6Reader(std::ifstream&& reader) 
    : PPMReader{ std::forward<std::ifstream>(reader) }
{}


void PPMP6Reader::ReadData(PPM& ppm) noexcept 
{
    auto& imageData = ppm.GetData();
    const auto& [height, width] = ppm.GetResolution();
    
    imageData.reserve(height);

    const std::size_t byteSize = sizeof(std::uint8_t); 
    const std::size_t extraByte = byteSize * (ppm.GetPixelMaxValue() > 255);   

    auto readBytes = [=](Pixel::Byte* byte)  
    {
        m_FileReader.read(reinterpret_cast<char*>(byte), byteSize + extraByte);
    };

    for (ImageFormat::ScreenResolution h = 0; h < height; ++h)
    {
        ImageFormat::DataRow row{};
        row.reserve(width);

        for (ImageFormat::ScreenResolution w = 0; w < width; ++w)
        {
            Pixel::Byte r, g, b;

            readBytes(&r);  
            readBytes(&g);
            readBytes(&b);

            row.push_back(Pixel{ r, g, b });
        }

        imageData.push_back(std::move(row));
    }
}

void PPMP6Reader::CheckHeader(const PPM& ppm) const noexcept(false)  
{

    if (const auto& format = ppm.GetFormat(); format != "P6")
    {
        throw std::runtime_error{ "The program does not support " + format + 
            " format of .ppm file type" };
    }
}
