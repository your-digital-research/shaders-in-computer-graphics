// Colored Fragment Shader
// Renders fragments with interpolated vertex colors including alpha transparency
// Creates smooth color gradients with transparency support

#version 330 core

// Input from vertex shader (interpolated across triangles)
in vec4 vColor;

// Output color for this fragment
out vec4 FragColor;

void main()
{
    // Output the interpolated vertex color with alpha
    FragColor = vColor;
}

