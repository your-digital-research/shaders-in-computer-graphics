#define GL_SILENCE_DEPRECATION

#include <iostream>
#include <random>

#include "core/engine.hpp"

// Temporary function for test
void DisplayRandomColor() {
    static std::mt19937 rng(static_cast<unsigned>(time(nullptr)));
    static std::uniform_real_distribution<float> dist(0.2f, 0.8f); // softer range
    static float r = dist(rng), g = dist(rng), b = dist(rng);
    static float targetR = dist(rng), targetG = dist(rng), targetB = dist(rng);

    // Smoothly interpolate toward the target
    constexpr float speed = 0.01f;
    r += (targetR - r) * speed;
    g += (targetG - g) * speed;
    b += (targetB - b) * speed;

    // If close to a target, pick a new one
    if (fabs(r - targetR) < 0.01f) targetR = dist(rng);
    if (fabs(g - targetG) < 0.01f) targetG = dist(rng);
    if (fabs(b - targetB) < 0.01f) targetB = dist(rng);

    glClearColor(r, g, b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

Engine::Engine(Window* window)
    : m_Window(window), m_Running(true)
{
    std::cout << "Engine created successfully!" << std::endl;
}

void Engine::Run() const
{
    while (m_Running && !m_Window->ShouldClose())
    {
        m_Window->PollEvents();

        DisplayRandomColor();

        m_Window->SwapBuffers();
    }
}
