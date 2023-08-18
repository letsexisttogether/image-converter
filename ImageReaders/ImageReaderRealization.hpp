#include <utility>

#include "ImageReader.hpp"

template<class _ImageFormat>
class ImageReaderRealization : public ImageReader
{
public:
    ImageReaderRealization(std::ifstream && reader)
        : ImageReader{ std::forward<std::ifstream>(reader) }
    {}

    virtual ~ImageReaderRealization() = default;

    ImageFormat Read() noexcept(false) override
    {
        ReadHeader();
        CheckHeader();

        ReadData(); 
        CheckData();

        return m_Image;
    }

protected:
    virtual void ReadHeader() noexcept = 0;
    virtual void ReadData() noexcept = 0;

    virtual void CheckHeader() const noexcept(false) = 0;
    virtual void CheckData() const noexcept(false) = 0;

protected:
    _ImageFormat m_Image{};
};
