#include "core/application.hpp"

#include <iostream>
#include <exception>

using namespace core;

int main()
{
    // std::cout << "Welcome to \"Shaders In Computer Graphics\" ^_^" << std::endl;

    try
    {
        const Application application;

        application.Run();

        return EXIT_SUCCESS;
    }
    catch (const std::exception& e)
    {
        std::cerr << "[Fatal Error] Application failed with exception: " << e.what() << std::endl;

        return EXIT_FAILURE;
    }
    catch (...)
    {
        std::cerr << "[Fatal Error] Application failed with unknown exception!" << std::endl;

        return EXIT_FAILURE;
    }
}
