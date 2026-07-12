#include "LedSim/Core/Application.hpp"

#include <cstdlib>
#include <iostream>

#include <GLFW/glfw3.h>
#include <glad/gl.h>

#include "LedSim/Graphics/Renderer.hpp"

static void ErrorCallback(int error, const char *description) {
  std::cerr << "GLFW Error " << error << ": " << description << '\n';
}

LedSim::Core::Application::~Application() {
  m_renderer.reset();
  if (m_window) {
    glfwDestroyWindow(m_window);
  }

  glfwTerminate();
}

bool LedSim::Core::Application::Initialize() {
  glfwSetErrorCallback(ErrorCallback);

  

  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW\n";
    return false;
  }

  framebuffer.At(10, 5).red = 255;
  framebuffer.At(11, 5).green = 255;
  framebuffer.At(12, 5).blue = 255;

  m_window = glfwCreateWindow(1280, 720, "LedSim", nullptr, nullptr);

  if (m_window == nullptr) {
    std::cerr << "Failed to create window\n";
    return false;
  }

  glfwMakeContextCurrent(m_window);

  if (!gladLoadGL(glfwGetProcAddress)) {
    std::cerr << "Failed to initialize GLAD\n";
    return false;
  }

  m_renderer = std::make_unique<LedSim::Graphics::Renderer>();
  if (!m_renderer->Initialize()) {
    return false;
  }

  glfwSwapInterval(1);

  std::cout << "Vendor   : "
            << reinterpret_cast<const char *>(glGetString(GL_VENDOR)) << '\n';

  std::cout << "Renderer : "
            << reinterpret_cast<const char *>(glGetString(GL_RENDERER)) << '\n';

  std::cout << "Version  : "
            << reinterpret_cast<const char *>(glGetString(GL_VERSION)) << '\n';

  std::cout << "GLSL     : "
            << reinterpret_cast<const char *>(
                   glGetString(GL_SHADING_LANGUAGE_VERSION))
            << '\n';

  return true;
}

void LedSim::Core::Application::Run() {
  while (!glfwWindowShouldClose(m_window)) {
    int width;
    int height;

    glfwGetFramebufferSize(m_window, &width, &height);

    m_renderer->BeginFrame(width, height);
    m_renderer->Draw(framebuffer);
    glfwSwapBuffers(m_window);

    m_renderer->EndFrame();

    glfwPollEvents();
  }
}