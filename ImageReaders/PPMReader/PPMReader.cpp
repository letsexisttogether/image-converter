#include "PPMReader.hpp"
#include "ImageFormats/ImageFormat.hpp"

#include <complex>
#include <ios>
#include <stdexcept>
#include <utility>

PPMReader::PPMReader(std::ifstream&& reader) 
    : ImageReaderRealization<PPM>{ std::forward<std::ifstream>(reader) }
{}

void PPMReader::ReadHeader(PPM& ppm) noexcept
{
    m_FileReader >> ppm.GetFormat() >> ppm.GetWidth() >> ppm.GetHeight()
        >> ppm.GetPixelMaxValue();

    m_FileReader.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    for (char smb; m_FileReader.get(smb); )
    {
        if (smb == '#')
        {
            std::string commentLine;
            std::getline(m_FileReader, commentLine);
        }
        else
        {
            m_FileReader.seekg(m_FileReader.tellg() - std::streamoff(1));

            break;
        }
    }
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

// TODO: rework the method
// Problem: doesn't throw an exception if a row contains less elements than width
void PPMReader::CheckData(const PPM& ppm) const noexcept(false)
{
    const auto& imageData = ppm.GetData();

    auto checkEachRowSize = [imageData](const ImageFormat::ScreenResolution width)
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

    if (const auto& [height, width] = ppm.GetResolution();
        imageData.size() != height || !checkEachRowSize(ppm.GetWidth()))
    {
        throw std::runtime_error{ "The data is corrupted" };
    }
}
