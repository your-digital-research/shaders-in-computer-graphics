// Colored Fragment Shader - Interpolated vertex colors

#version 330 core

// Input from vertex shader
in vec4 vColor;

// Output
out vec4 FragColor;

void main()
{
    // Output interpolated color from vertices
    FragColor = vColor;
}

