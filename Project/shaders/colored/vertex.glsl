// Colored Vertex Shader
// Transforms vertex positions and passes vertex colors to fragment shader
// Supports per-vertex coloring with RGBA (alpha transparency support)

#version 330 core

// Input vertex attributes
layout(location = 0) in vec3 aPosition;  // Vertex position in model space
layout(location = 1) in vec4 aColor;     // Vertex color (RGBA)

// Output to fragment shader
out vec4 vColor;  // Interpolated color with alpha

// Uniform matrices for transformations
uniform mat4 uModel;       // Model matrix (local to world space)
uniform mat4 uView;        // View matrix (world to camera space)
uniform mat4 uProjection;  // Projection matrix (camera to clip space)

void main()
{
    // Pass color to fragment shader (will be interpolated)
    vColor = aColor;

    // Transform vertex position: Model -> View -> Projection
    gl_Position = uProjection * uView * uModel * vec4(aPosition, 1.0);
}

