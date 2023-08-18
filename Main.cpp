#include <cstdint>
#include <exception>
#include <fstream>
#include <iostream>
#include <memory>
#include <ostream>

#include "ImageReaders/BMP/BMPReader.hpp"
#include "ImagePreparators/PPM/PPMPreparator.hpp"
#include "ImageWriters/PPMWriter/PPMWriter.hpp"

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

    if (argc < 2)
    {
        std::cerr << "The arguments does not specify the needed amount\n";
        
        return EXIT_FAILURE;
    }
    
    try
    {
        std::unique_ptr<ImageReader> reader{ new BMPReader{ std::ifstream{ argv[1], 
            std::ios::binary } } };
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
