// UV Fragment Shader - Visualizes UV coordinates as colors
// U → Red, V → Green
// (0, 0) = Black, (1, 0) = Red, (1, 1) = Yellow, (0, 1) = Green

#version 330 core

// Input from vertex shader
in vec2 vUV;

// Output
out vec4 FragColor;

void main()
{
    // Map UV coordinates to RGB (U → Red, V → Green)
    FragColor = vec4(vUV.x, vUV.y, 0.0, 1.0);
}

