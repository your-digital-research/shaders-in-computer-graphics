// UV Vertex Shader - Passes UV coordinates for visualization

#version 330 core

// Vertex attributes
layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec4 aColor;
layout(location = 2) in vec2 aUV;

// Output to fragment shader
out vec2 vUV;

// Transformation matrices
uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

void main()
{
    // Pass UV coordinates to fragment shader for interpolation
    vUV = aUV;

    // Transform position to clip space
    gl_Position = uProjection * uView * uModel * vec4(aPosition, 1.0);
}

