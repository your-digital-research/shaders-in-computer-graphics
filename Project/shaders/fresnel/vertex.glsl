// Sphere Vertex Shader - Fresnel rim lighting

#version 330 core

// Vertex attributes
layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec4 aColor;
layout(location = 2) in vec2 aTexCoord;

// Output to fragment shader
out vec3 vPosition;
out vec3 vNormal;
out vec4 vColor;
out vec2 vTexCoord;

// Transformation matrices
uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

void main()
{
    // Calculate world space position
    vec4 worldPos = uModel * vec4(aPosition, 1.0);
    vPosition = worldPos.xyz;

    // Calculate normal (for sphere, normalized position is the normal)
    vNormal = normalize(mat3(uModel) * aPosition);

    // Pass data to fragment shader
    vColor = aColor;
    vTexCoord = aTexCoord;

    // Transform to clip space
    gl_Position = uProjection * uView * worldPos;
}
