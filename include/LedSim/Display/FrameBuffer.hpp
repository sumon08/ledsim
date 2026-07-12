#ifndef LEDSIM_DISPLAY_FRAMEBUFFER_HPP
#define LEDSIM_DISPLAY_FRAMEBUFFER_HPP

#include <vector>

#include "LedSim/Display/Pixel.hpp"


namespace LedSim::Display {

class FrameBuffer
{
public:
    FrameBuffer(int width, int height);

    int Width() const;
    int Height() const;

    Pixel& At(int x, int y);
    const Pixel& At(int x, int y) const;

    const Pixel* Data() const;

private:
    int width;
    int height;

    std::vector<Pixel> pixels;
};

} // namespace LedSim::Display

#endif // LEDSIM_DISPLAY_FRAMEBUFFER_HPP