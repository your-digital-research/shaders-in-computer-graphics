#pragma once

#include <string>

#include "graphics/gl.hpp"

namespace platform
{
    using namespace std;

    class Window
    {
    public:
        Window(int width, int height, const string& title);
        ~Window();

        [[nodiscard]] GLFWwindow* GetNativeWindow() const;
        [[nodiscard]] bool ShouldClose() const;

        void PollEvents();
        void SwapBuffers();

        [[nodiscard]] int GetWidth() const { return m_Width; }
        [[nodiscard]] int GetHeight() const { return m_Height; }

        [[nodiscard]] float GetAspectRatio() const
        {
            return static_cast<float>(m_Width) / static_cast<float>(m_Height);
        }

        void OnFramebufferResize();
        void OnWindowFocus();
        void InitializeRenderer() const;

    private:
        static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
        static void WindowFocusCallback(GLFWwindow* window, int focused);
        static void WindowSizeCallback(GLFWwindow* window, int width, int height);

        GLFWwindow* m_Window;
        int m_Width;
        int m_Height;
    };
}
