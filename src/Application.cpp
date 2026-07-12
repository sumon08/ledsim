#include "Application.h"

#include <cstdlib>
#include <iostream>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

static void ErrorCallback(int error, const char* description)
{
    std::cerr << "GLFW Error " << error
              << ": "
              << description
              << '\n';
}

Application::Application()
    : m_window(nullptr)
{
}

Application::~Application()
{
    if (m_window != nullptr)
    {
        glfwDestroyWindow(m_window);
    }

    glfwTerminate();
}

bool Application::Initialize()
{
    glfwSetErrorCallback(ErrorCallback);

    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW\n";
        return false;
    }

    m_window = glfwCreateWindow(
        1280,
        720,
        "LedSim",
        nullptr,
        nullptr);

    if (m_window == nullptr)
    {
        std::cerr << "Failed to create window\n";
        return false;
    }

    glfwMakeContextCurrent(m_window);

    if (!gladLoadGL(glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD\n";
        return false;
    }

    glfwSwapInterval(1);

    std::cout << "Vendor   : "
              << reinterpret_cast<const char*>(glGetString(GL_VENDOR))
              << '\n';

    std::cout << "Renderer : "
              << reinterpret_cast<const char*>(glGetString(GL_RENDERER))
              << '\n';

    std::cout << "Version  : "
              << reinterpret_cast<const char*>(glGetString(GL_VERSION))
              << '\n';

    std::cout << "GLSL     : "
              << reinterpret_cast<const char*>(
                     glGetString(GL_SHADING_LANGUAGE_VERSION))
              << '\n';

    return true;
}

void Application::Run()
{
    while (!glfwWindowShouldClose(m_window))
    {
        int width;
        int height;

        glfwGetFramebufferSize(m_window, &width, &height);

        glViewport(0, 0, width, height);

        glClearColor(0.08f, 0.08f, 0.08f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
}