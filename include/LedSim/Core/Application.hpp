



#ifndef LEDSIM_CORE_APPLICATION_HPP
#define LEDSIM_CORE_APPLICATION_HPP

#include "LedSim/Display/FrameBuffer.hpp"
#include "LedSim/Graphics/Renderer.hpp"
#include <memory>

struct GLFWwindow;

namespace LedSim::Core {

    

class Application
{
public:
    Application() = default;
    ~Application();

    bool Initialize();
    void Run();

private:
    GLFWwindow* m_window = nullptr;
    std::unique_ptr<LedSim::Graphics::Renderer> m_renderer;
    LedSim::Display::FrameBuffer framebuffer{64, 32};
};

} // namespace LedSim::Core
#endif // LEDSIM_CORE_APPLICATION_HPP