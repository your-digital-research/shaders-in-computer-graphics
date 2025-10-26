#pragma once

#include "platform/window.hpp"
#include "core/engine.hpp"

namespace core
{
    class Application
    {
    public:
        // Constructor and Destructor
        Application();
        ~Application();

        // Application management
        void Run() const;

    private:
        // Member variables
        platform::Window *m_Window = nullptr;
        Engine *m_Engine = nullptr;

        // Initialization and shutdown
        void Initialize();
        void Shutdown();
    };
}
