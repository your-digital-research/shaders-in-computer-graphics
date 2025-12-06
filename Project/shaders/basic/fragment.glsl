// Basic Fragment Shader - Renders with uniform color

#version 330 core

// Output
out vec4 FragColor;

// Uniforms
uniform vec4 uColor;

void main()
{
    // Output uniform color
    FragColor = uColor;
}
