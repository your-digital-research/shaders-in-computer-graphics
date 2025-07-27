#pragma once

#include "platform/window.hpp"

class Application
{
public:
    // Constructor and Destructor
    Application();
    ~Application();

    // Application management
    void Run();

private:
    // Member variables
    Window *m_Window = nullptr;

    // Initialization, main loop, and shutdown
    void Initialize();
    void StartLoop();
    void Shutdown();
};