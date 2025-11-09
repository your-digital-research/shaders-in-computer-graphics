#pragma once

#include <string>

#include "graphics/gl.hpp"

namespace platform
{
    class Window
    {
    public:
        // Constructor and Destructor
        Window(int width, int height, const std::string& title);
        ~Window();

        // Getters
        [[nodiscard]] GLFWwindow* GetNativeWindow() const;

        // Window state
        [[nodiscard]] bool ShouldClose() const;

        // Window management
        void PollEvents() const;
        void SwapBuffers() const;

    private:
        // Member variables
        GLFWwindow* m_Window;
    };
}
