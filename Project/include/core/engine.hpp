#pragma once

#include "platform/window.hpp"
#include "graphics/renderer.hpp"

class Engine
{
public:
    // Constructor and Destructor
    explicit Engine(Window* window);
    ~Engine() = default;

    // Engine management
    void Run() const;

private:
    // Member variables
    Window* m_Window;
    graphics::Renderer* m_Renderer;

    // Engine state
    bool m_Running;

    // Initialization
    void Initialize();
};
