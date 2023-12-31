#include "PPMWriter.hpp"

#include "ImageWriters/PPM/ImagePreparator/PPMPreparator.hpp"
#include "ImageWriters/PPM/DataCoders/P3/P3DataCoder.hpp"
#include "ImageWriters/PPM/DataCoders/P6/P6DataCoder.hpp"

PPMWriter::PPMWriter(std::ofstream&& fileWriter, 
            ImagePreparator<PPM>&& preparator, Fabric&& fabric)
    : ImageWriterRealization<PPM>{ std::forward<std::ofstream>(fileWriter) },
        m_Image{ std::move(preparator.PrepareImage()) }, m_Fabric{ fabric }
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

// DLL
extern "C" __declspec(dllexport) ImageWriter* CreateWriter
    (std::ofstream&& writer, ImageFormat&& image)
{
    PPMWriter::Fabric fabric
    {
        PPMWriter::Fabric::FunctionsMap
        {
            { 
                "P3", [] (std::ofstream& writer, const PPM& ppm) -> PPMDataCoder*
                {
                    return new P3DataCoder{ writer };
                }
            },
            { 
                "P6", [] (std::ofstream& writer, const PPM& ppm) -> PPMDataCoder*
                {
                    return new P6DataCoder{ writer, ppm };
                }
            }
        }
    };

    return new PPMWriter{ std::move(writer), 
        PPMPreparator{ std::move(image) }, std::move(fabric) };

}
