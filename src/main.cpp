#include "LedSim/Core/Application.hpp"

#include <cstdlib>

int main()
{
    LedSim::Core::Application app;

    if (!app.Initialize())
    {
        return EXIT_FAILURE;
    }

    app.Run();

    return EXIT_SUCCESS;
}