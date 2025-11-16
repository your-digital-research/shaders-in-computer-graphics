// Basic Fragment Shader
// Renders all fragments with a single uniform color
// Used for simple solid-colored geometry

#version 330 core

// Output color for this fragment
out vec4 FragColor;

// Uniform color
uniform vec4 uColor;

void main()
{
    // Output the uniform color for all fragments
    FragColor = uColor;
}
