#include <iostream>

#include "core/application.h"

int main()
{
    std::cout << "Hello, Terrafabric!" << std::endl;

    try
    {
        Application app;
        app.run();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}