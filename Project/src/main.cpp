#include "core/application.hpp"
#include <iostream>

int main()
{
    // This is the main entry point of the application.
    std::cout << "Welcome to \"Shaders In Computer Graphics\" ^_^" << std::endl;

    // Create an instance of the Application class.
    Application application;

    // Run the application.
    application.Run();

    return 0;
}