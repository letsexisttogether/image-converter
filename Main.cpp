#include <cstdint>
#include <exception>
#include <fstream>
#include <iostream>
#include <memory>
#include <ostream>

#include "ImageReaders/BMP/BMPReader.hpp"
#include "ImagePreparators/PPM/PPMPreparator.hpp"
#include "ImageWriters/PPMWriter/PPMWriter.hpp"
#include "ImageReaders/BMP/BMPPixelParsers/BMP32PixelParser/BMP32PixelParser.hpp"
#include "ImageReaders/BMP/BMPPixelParsers/BMP8PixelParser/BMP8PixelParser.hpp"

void PrintImage(const ImageFormat& image)
{
    const auto& [height, width] = image.GetResolution();

    std::cout << "Height: " << height << " Width: " << width 
        << "\nData:\n";

    for (ImageFormat::ScreenResolution h = 0; h < height; ++h)
    {
        for (ImageFormat::ScreenResolution w = 0; w < width; ++w)
        {
            const Pixel& pixel = image.GetPixel(h, w);

            std::cout << pixel.Red << ' ' 
                << pixel.Green << ' '<< pixel.Blue << '\n';
        }
    }

    std::cout << "\nEnd of print" << std::endl;
}

std::int32_t main(std::int32_t argc, const char** argv)
{
    std::cout << "Hello, neovim" << std::endl; 

    if (argc < 3)
    {
        std::cerr << "The arguments does not specify the needed amount\n";
        
        return EXIT_FAILURE;
    }
    
    try
    {
        std::unique_ptr<ImageReader> reader
        { 
            new BMPReader
            { 
                std::ifstream{ argv[1], std::ios::binary },
                BMPParsersFabric
                {
                    BMPParsersFabric::FunctionsMap
                    {
                        { 0x1, [](const BMP& bmp) -> BMPPixelParser* 
                            { return new BMP8PixelParser(bmp, 0b1); } },
                        { 0x2, [](const BMP& bmp) -> BMPPixelParser* 
                            { return new BMP8PixelParser(bmp, 0b11); } },
                        { 0x4, [](const BMP& bmp) -> BMPPixelParser* 
                            { return new BMP8PixelParser(bmp, 0b1111); } },
                        { 0x8, [](const BMP& bmp) -> BMPPixelParser* 
                            { return new BMP8PixelParser(bmp, 0x11111111); } },
                        { 0x10, [](const BMP& bmp) -> BMPPixelParser* 
                            { return new BMP32PixelParser(bmp, 0x1111, true); } },
                        { 0x18, [](const BMP& bmp) -> BMPPixelParser* 
                            { return new BMP32PixelParser(bmp, 0b11111111, false); } },
                        { 0x20, [](const BMP& bmp) -> BMPPixelParser* 
                            { return new BMP32PixelParser(bmp, 0b11111111, true); } }
                    }
                }
            } 
        };
        const ImageFormat image{ reader->Read() };

        PPM signature
        {
            std::move(image)
        };

        std::unique_ptr<ImagePreparator> preparator{ new PPMPreparator{ signature } };
        preparator->PrepareImage();

        std::unique_ptr<ImageWriter> writer
        { 
            new PPMWriter
            { 
                std::ofstream{ argv[2] }, 
                signature
            } 
        };
        std::cout << "Breakpoint" << std::endl;
        writer->Write();

    }    
    catch (std::exception& exp)
    {
        std::cerr << exp.what() << std::endl;

        return EXIT_FAILURE;
    }
    
    std::cout << "The end";

    return EXIT_SUCCESS;
}
