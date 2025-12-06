// Basic Vertex Shader - Transforms vertices using MVP matrices

#version 330 core

// Vertex attributes
layout(location = 0) in vec3 aPosition;

// Transformation matrices
uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

void main()
{
    // Transform position to clip space
    gl_Position = uProjection * uView * uModel * vec4(aPosition, 1.0);
}
