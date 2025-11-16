#include <iostream>

#include "graphics/renderer.hpp"

namespace graphics
{
    using namespace std;

    Renderer::Renderer()
    {
        Initialize();
    }

    void Renderer::Initialize()
    {
        // Initialize GLAD
        if (!gladLoadGL())
        {
            cerr << "[OpenGL Error] Failed to initialize GLAD!" << endl;

            return;
        }

        // Print OpenGL version
        // cout << "OpenGL Version: " << glGetString(GL_VERSION) << endl;
        // cout << "OpenGL Vendor: " << glGetString(GL_VENDOR) << endl;
        // cout << "OpenGL Renderer: " << glGetString(GL_RENDERER) << endl;
        // cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;

        // Set default OpenGL state
        EnableDepthTest();
        EnableBlending();

        // Set default depth function
        glDepthFunc(GL_LESS);

        // Set default blend function
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void Renderer::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Reset depth buffer
        glClearDepth(1.0f);
    }

    void Renderer::SetClearColor(const vec3& color, const float alpha)
    {
        glClearColor(color.r, color.g, color.b, alpha);
    }

    void Renderer::SetClearColor(const vec4& color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void Renderer::EnableDepthTest()
    {
        glEnable(GL_DEPTH_TEST);
    }

    void Renderer::DisableDepthTest()
    {
        glDisable(GL_DEPTH_TEST);
    }

    void Renderer::EnableBlending()
    {
        glEnable(GL_BLEND);
    }

    void Renderer::DisableBlending()
    {
        glDisable(GL_BLEND);
    }

    void Renderer::SetViewport(const int x, const int y, const int width, const int height)
    {
        glViewport(x, y, width, height);
    }
}
