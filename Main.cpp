#include <cstdint>
#include <exception>
#include <fstream>
#include <iostream>
#include <memory>
#include <ostream>

#include "ImageFormats/ImageFormat.hpp"
#include "ImageReaders/ImageReader.hpp"
#include "ImageWriters/ImageWriter.hpp"
#include "SharedLibLoaders/WindowsLibLoader/WindowsLibLoader.hpp"

std::int32_t main(std::int32_t argc, const char** argv)
{
    std::cout << "Hello, neovim" << std::endl; 

    if (argc < 3)
    {
        std::cerr << "The arguments does not specify the needed amount\n";
        
        std::cout << sizeof(std::int32_t*) << std::endl;

        return EXIT_FAILURE;
    }
    
    try
    { 
        std::unique_ptr<SharedLibLoader<ImageReader, std::ifstream&&>> readerLoader
        { 
            new WindowsLibLoader<ImageReader, std::ifstream&&>
            { 
                "ImageReaders/BMPReader.dll", "CreateReader"
            }
        };

        readerLoader->LoadLib();

        std::unique_ptr<SharedLibLoader<ImageWriter, std::ofstream&&, ImageFormat&&>>
            writerLoader
        { 
            new WindowsLibLoader<ImageWriter, std::ofstream&&, ImageFormat&&>
            { 
                "ImageWriters/PPMWriter.dll", "CreateWriter"
            }
        };

        writerLoader->LoadLib();


        std::unique_ptr<ImageReader> reader
        {
            readerLoader->SpawnObject(std::ifstream{ argv[1], std::ios::binary })
        };

        ImageFormat image{ reader->Read() };

        std::unique_ptr<ImageWriter> writer
        {
            writerLoader->SpawnObject(std::ofstream{ argv[2] }, std::move(image))
        }; 
        
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
