#define GL_SILENCE_DEPRECATION

#include <glad/glad.h> // Must be included before GLFW
#include <GLFW/glfw3.h>
#include <iostream>

int main()
{
    // NOTE - This is the main entry point of the application.

    std::cout << "Welcome to \"Shaders In Computer Graphics\" ^_^" << std::endl;

    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW\n";

        return -1;
    }

    GLFWwindow *window = glfwCreateWindow(800, 600, "Shaders In Computer Graphics", nullptr, nullptr);

    if (!window)
    {
        std::cerr << "Failed to create GLFW window\n";

        glfwTerminate();

        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;

        return -1;
    }

    while (!glfwWindowShouldClose(window))
    {
        // Rendering code will go here
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}