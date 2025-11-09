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

        // Window properties
        [[nodiscard]] int GetWidth() const { return m_Width; }
        [[nodiscard]] int GetHeight() const { return m_Height; }
        [[nodiscard]] float GetAspectRatio() const { return static_cast<float>(m_Width) / static_cast<float>(m_Height); }

        // Update notification
        void OnFramebufferResize();
        void OnWindowFocus();

    private:
        // Callback handling
        static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
        static void WindowFocusCallback(GLFWwindow* window, int focused);
        static void WindowSizeCallback(GLFWwindow* window, int width, int height);

        // Member variables
        GLFWwindow* m_Window;
        int m_Width;
        int m_Height;
    };
}
