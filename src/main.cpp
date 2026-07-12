#include "Application.h"

#include <cstdlib>

int main()
{
    Application app;

    if (!app.Initialize())
    {
        return EXIT_FAILURE;
    }

    app.Run();

    return EXIT_SUCCESS;
}