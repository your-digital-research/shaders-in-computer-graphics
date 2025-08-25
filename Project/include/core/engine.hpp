#pragma once

#include "platform/window.hpp"

class Engine
{
public:
    // Constructor and Destructor
    explicit Engine(Window *window);
    ~Engine() = default;

    // Engine management
    void Run() const;

private:
    // Member variables
    Window *m_Window;

    // Engine state
    bool m_Running;
};