#include <iostream>

#include "core/application.hpp"

using namespace std;
using namespace core;

int main()
{
    // This is the main entry point of the application.
    cout << "Welcome to \"Shaders In Computer Graphics\" ^_^" << endl;

    // Create an instance of the Application class.
    const Application application;

    // Run the application.
    application.Run();

    return 0;
}
