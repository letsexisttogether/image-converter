#include "PPMReader.hpp"
#include "ImageFormats/ImageFormat.hpp"

#include <complex>
#include <stdexcept>
#include <utility>

PPMReader::PPMReader(std::ifstream&& reader) 
    : ImageReaderRealization<PPM>{ std::forward<std::ifstream>(reader) }
{}

void PPMReader::ReadHeader(PPM& ppm) noexcept
{
    m_FileReader >> ppm.GetFormat() >> ppm.GetWidth() >> ppm.GetHeight()
        >> ppm.GetPixelMaxValue();
}

void PPMReader::ReadData(PPM& ppm) noexcept 
{
    auto& imageData = ppm.GetData();
    const auto& [height, width] = ppm.GetResolution();
    
    imageData.reserve(height);

    for (ImageFormat::ScreenResolution h = 0; h < height; ++h)
    {
        ImageFormat::DataRow row{};
        row.reserve(width);

        for (ImageFormat::ScreenResolution w = 0; w < width; ++w)
        {
            Pixel pixel;
            m_FileReader >> pixel;

            row.push_back(pixel);
        }

        imageData.push_back(std::move(row));
    }
}

void PPMReader::CheckHeader(const PPM& ppm) const noexcept(false)
{
    if (const auto& format = ppm.GetFormat(); format != "P3")
    {
        throw std::runtime_error{ "The program does not support " + format + 
            " format of .ppm file type" };
    }
}

void PPMReader::CheckData(const PPM& ppm) const noexcept(false)
{
    auto& imageData = ppm.GetData();
    const auto& [height, width] = ppm.GetResolution();

    // Get a reason about passing width like that and explain or change it later
    auto checkEachRowSize = [&imageData](const ImageFormat::ScreenResolution width)
    {
        for (const auto& row : imageData)
        {
            if (row.size() != width)
            {
                return false;
            }
        }

        return true;
    };

    if (const ImageFormat::ScreenResolution size = imageData.size();
            size != height || !checkEachRowSize(width))
    {
        throw std::runtime_error{ "The data is corrupted" };
    }
}
