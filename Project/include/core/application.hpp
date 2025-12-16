#pragma once

#include "platform/window.hpp"
#include "core/engine.hpp"

namespace core
{
    using namespace platform;

    class Application
    {
    public:
        Application();
        ~Application();

        void Run() const;

    private:
        Window* m_Window = nullptr;
        Engine* m_Engine = nullptr;

        void Initialize();
        void Shutdown();
    };
}
