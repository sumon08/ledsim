#pragma once

struct GLFWwindow;

class Application
{
public:
    Application();
    ~Application();

    bool Initialize();
    void Run();

private:
    GLFWwindow* m_window;
};