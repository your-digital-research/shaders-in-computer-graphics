#pragma once

#include <string>

#include "graphics/gl.hpp"

class Window
{
public:
    // Constructor and Destructor
    Window(int width, int height, const std::string& title);
    ~Window();

    // Getters
    GLFWwindow* GetNativeWindow() const;

    // Window management
    bool ShouldClose() const;
    void PollEvents() const;
    void SwapBuffers() const;

private:
    // Member variables
    GLFWwindow* m_Window;
};
