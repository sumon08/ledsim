

#ifndef LEDSIM_GRAPHICS_RENDERER_HPP
#define LEDSIM_GRAPHICS_RENDERER_HPP

namespace LedSim::Graphics {

class Renderer
{
public:
    Renderer();
    ~Renderer();

    bool Initialize();

    void BeginFrame(int width, int height);
    void EndFrame();
};
} // namespace LedSim::Graphics

#endif // LEDSIM_GRAPHICS_RENDERER_HPP