#include <GLFW/glfw3.h>

#include <cstdlib>
#include <iostream>

static void ErrorCallback(int error, const char *description)
{
    std::cerr << "GLFW Error " << error << ": " << description << std::endl;
}

int main()
{
    glfwSetErrorCallback(ErrorCallback);

    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW\n";
        return EXIT_FAILURE;
    }

    std::cout << "Vendor   : " << glGetString(GL_VENDOR) << '\n';
    std::cout << "Renderer : " << glGetString(GL_RENDERER) << '\n';
    std::cout << "Version  : " << glGetString(GL_VERSION) << '\n';

    // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window =
        glfwCreateWindow(1280, 720, "LedSim", nullptr, nullptr);

    if (window == nullptr)
    {
        std::cerr << "Failed to create window\n";
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    while (!glfwWindowShouldClose(window))
    {
        glViewport(0, 0, 1280, 720);

        glClearColor(0.08f, 0.08f, 0.08f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return EXIT_SUCCESS;
}