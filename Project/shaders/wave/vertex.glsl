// Wave Vertex Shader - Radial ripple effect from center

#version 330 core

// Vertex attributes
layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec4 aColor;

// Output to fragment shader
out vec4 vColor;
out float vDistFromCenter;
out float vHeight;
out vec3 vWorldPos;

// Transformation matrices
uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

// Wave parameters
uniform float uTime;
uniform float uWaveAmplitude;
uniform float uWaveFrequency;
uniform float uPlaneRadius;

void main()
{
    // Calculate distance from center in XZ plane
    float distFromCenter = length(aPosition.xz);

    // Create radial wave emanating from center
    float wave = sin(distFromCenter * uWaveFrequency - uTime) * uWaveAmplitude;

    // Smooth the center to avoid sharp peak
    float centerSmoothing = smoothstep(0.0, 0.5, distFromCenter);
    wave *= centerSmoothing;

    // Apply edge falloff for natural appearance
    float falloffStart = uPlaneRadius * 0.90;
    float falloffEnd = uPlaneRadius * 1.06;
    float falloff = 1.0 - smoothstep(falloffStart, falloffEnd, distFromCenter);
    wave *= falloff;

    // Apply wave displacement to Y position
    vec3 displacedPosition = aPosition;
    displacedPosition.y += wave;

    // Pass data to fragment shader
    vColor = aColor;
    vDistFromCenter = distFromCenter;
    vHeight = wave;
    vWorldPos = vec3(uModel * vec4(displacedPosition, 1.0));

    // Transform to clip space with displacement
    gl_Position = uProjection * uView * uModel * vec4(displacedPosition, 1.0);
}
