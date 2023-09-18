#include "PPMReader.hpp"

#include <complex>
#include <ios>
#include <stdexcept>
#include <utility>
#include <memory>

#include "DataParsers/P3/P3DataParser.hpp"
#include "DataParsers/P6/P6DataParser.hpp"

PPMReader::PPMReader(std::ifstream&& reader, Fabric&& fabric)
    : ImageReaderRealization<PPM>{ std::forward<std::ifstream>(reader) },
        m_Fabric{ std::move(fabric) }
{}

void PPMReader::ReadHeader() noexcept
{
    m_FileReader >> m_Image.Format; 

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

    m_FileReader >> m_Image.Width >> m_Image.Height
        >> m_Image.PixelMaxValue;

    m_FileReader.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void PPMReader::ReadData() noexcept 
{
    auto& imageData = m_Image.Data;
    const auto& [height, width] = m_Image.GetResolution();
    
    std::unique_ptr<PPMDataParser> parser
        { m_Fabric.SpawnObject(m_Image.Format, m_FileReader, m_Image) };

    imageData.reserve(height);

    for (ImageFormat::ScreenResolution h = 0; h < height; ++h)
    {
        ImageFormat::DataRow row{};
        row.reserve(width);

        for (ImageFormat::ScreenResolution w = 0; w < width; ++w)
        {
            row.push_back(parser->ReadPixel());
        }

        imageData.push_back(std::move(row));
    }
}

void PPMReader::CheckHeader() const noexcept(false)
{
    if (const auto& format = m_Image.Format; format != "P3")
    {
        throw std::runtime_error{ "The program does not support " + format + 
            " format of .m_Image file type" };
    }
}

// TODO: rework the method
// Problem: doesn't throw an exception if a row contains less elements than width
void PPMReader::CheckData() const noexcept(false)
{
    const auto& imageData = m_Image.Data;

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

    if (const auto& [height, width] = m_Image.GetResolution();
        imageData.size() != height || !checkEachRowSize(m_Image.Width))
    {
        throw std::runtime_error{ "The data is corrupted" };
    }
}

// DLL 
extern "C" __declspec(dllexport) ImageReader* CreateReader
    (std::ifstream&& reader)
{
    // Yes, we hardcode it
    PPMReader::Fabric fabric
    {
        PPMReader::Fabric::FunctionsMap
        {
            { 
                "P3", [] (std::ifstream& reader, const PPM& ppm) -> PPMDataParser*
                { return new P3DataParser{ reader }; }
            },
            { 
                "P6", [] (std::ifstream& reader, const PPM& ppm) -> PPMDataParser*
                { return new P6DataParser{ reader, ppm }; }
            },
        }
    };

    return new PPMReader{ std::forward<std::ifstream>(reader), 
        std::move(fabric) };
}
