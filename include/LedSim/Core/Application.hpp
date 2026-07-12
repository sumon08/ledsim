



#ifndef LEDSIM_CORE_APPLICATION_HPP
#define LEDSIM_CORE_APPLICATION_HPP

#include "LedSim/Graphics/Renderer.hpp"

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

    LedSim::Graphics::Renderer m_renderer;
};

} // namespace LedSim::Core
#endif // LEDSIM_CORE_APPLICATION_HPP