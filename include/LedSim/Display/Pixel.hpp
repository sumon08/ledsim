#ifndef LEDSIM_DISPLAY_PIXEL_HPP
#define LEDSIM_DISPLAY_PIXEL_HPP

#include <cstdint>

namespace LedSim::Display {

struct Pixel
{
    std::uint8_t red = 0;
    std::uint8_t green = 0;
    std::uint8_t blue = 0;
};

} // namespace LedSim::Display

#endif // LEDSIM_DISPLAY_PIXEL_HPP