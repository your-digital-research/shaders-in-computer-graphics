// Colored Vertex Shader - Per-vertex colors with interpolation

#version 330 core

// Vertex attributes
layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec4 aColor;

// Output to fragment shader
out vec4 vColor;

// Transformation matrices
uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

void main()
{
    // Pass color to fragment shader for interpolation
    vColor = aColor;

    // Transform position to clip space
    gl_Position = uProjection * uView * uModel * vec4(aPosition, 1.0);
}
