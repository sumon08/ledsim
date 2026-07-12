#include <cstdlib>
#include <iostream>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

static void ErrorCallback(int error, const char* description)
{
    std::cerr << "GLFW Error " << error << ": " << description << '\n';
}

int main()
{
    glfwSetErrorCallback(ErrorCallback);

    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW\n";
        return EXIT_FAILURE;
    }

    GLFWwindow* window = glfwCreateWindow(
        1280,
        720,
        "LedSim",
        nullptr,
        nullptr);

    if (window == nullptr)
    {
        std::cerr << "Failed to create window\n";
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGL(glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD\n";

        glfwDestroyWindow(window);
        glfwTerminate();

        return EXIT_FAILURE;
    }

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

    glfwSwapInterval(1);

    while (!glfwWindowShouldClose(window))
    {
        int width;
        int height;

        glfwGetFramebufferSize(window, &width, &height);

        glViewport(0, 0, width, height);

        glClearColor(0.08f, 0.08f, 0.08f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return EXIT_SUCCESS;
}