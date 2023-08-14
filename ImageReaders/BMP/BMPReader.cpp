#include "BMPReader.hpp"

BMPReader::BMPReader(std::ifstream&& reader) 
    : ImageReaderRealization<BMP>{ std::forward<std::ifstream>(reader) }
{}

void BMPReader::ReadHeader() noexcept
{
    m_FileReader >> m_Image.HeaderField >> m_Image.FileSize >> m_Image.Reserved[0] 
        >> m_Image.Reserved[1] >> m_Image.DataOffset;

    m_FileReader >> m_Image.InfoHeaderSize >> m_Image.Width >> m_Image.Height >> m_Image.ColorPlanesNumber
        >> m_Image.BitsPerPixel >> m_Image.CompressionMethod >> m_Image.ImageSize 
        >> m_Image.HorizontalResolution >> m_Image.VertivalResolution 
        >> m_Image.ColorPaletteNumber >> m_Image.ImportantColorsNumber;
}

void BMPReader::ReadData() noexcept 
{
    ReadColorTable();

    // TODO: make CheckColorTable();

    m_FileReader.seekg(m_Image.DataOffset, std::ios_base::beg);
    
     
}

void BMPReader::CheckHeader() const noexcept(false)
{}

void BMPReader::CheckData() const noexcept(false)
{}
