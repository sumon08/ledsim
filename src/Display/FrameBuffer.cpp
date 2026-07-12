#include "LedSim/Display/FrameBuffer.hpp"

namespace LedSim::Display {

FrameBuffer::FrameBuffer(int wdth, int hght)
    : width(wdth),
      height(hght),
      pixels(static_cast<std::size_t>(wdth * hght))
{
}

int FrameBuffer::Width() const
{
    return width;
}

int FrameBuffer::Height() const
{
    return height;
}

Pixel& FrameBuffer::At(int x, int y)
{
    return pixels[static_cast<std::size_t>(y * width + x)];
}

const Pixel& FrameBuffer::At(int x, int y) const
{
    return pixels[static_cast<std::size_t>(y * width + x)];
}

const Pixel* FrameBuffer::Data() const
{
    return pixels.data();
}

} // namespace LedSim::Display