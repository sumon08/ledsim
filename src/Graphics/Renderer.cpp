#include "LedSim/Graphics/Renderer.hpp"
#include <glad/gl.h>
#include <GLFW/glfw3.h>

LedSim::Graphics::Renderer::Renderer()
{
}

LedSim::Graphics::Renderer::~Renderer()
{
}

bool LedSim::Graphics::Renderer::Initialize()
{
    return true;
}

void LedSim::Graphics::Renderer::BeginFrame(int width, int height)
{
    glViewport(0, 0, width, height);

    glClearColor(0.08f, 0.08f, 0.08f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void LedSim::Graphics::Renderer::EndFrame()
{
}