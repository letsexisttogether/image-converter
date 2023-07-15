#include <cstdint>
#include <exception>
#include <fstream>
#include <iostream>
#include <memory>

#include "ImageFormats/ImageFormat.hpp"
#include "ImageReaders/PPMReader/PPMReader.hpp"
#include "Pixel/Pixel.hpp"

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

            std::cout << pixel.GetRed() << ' ' 
                << pixel.GetGreen() << ' '<< pixel.GetBlue() << '\n';
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
        std::unique_ptr<ImageReader> reader{ new PPMReader{ std::ifstream{ argv[1] } } };
        const ImageFormat image{ reader->Read() };

        PrintImage(image);
    }
    catch (std::exception& exp)
    {
        std::cerr << exp.what() << std::endl;
    }
    
    std::cout << "The end";

    return EXIT_SUCCESS;
}
