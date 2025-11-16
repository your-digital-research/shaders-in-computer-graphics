// Colored Fragment Shader
// Renders fragments with interpolated vertex colors
// Creates smooth color gradients across geometry

#version 330 core

// Input from vertex shader (interpolated across triangles)
in vec3 vColor;

// Output color for this fragment
out vec4 FragColor;

void main()
{
    // Output the interpolated vertex color with full opacity
    FragColor = vec4(vColor, 1.0);
}

