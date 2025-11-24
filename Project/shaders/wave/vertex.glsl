// Wave Plane Vertex Shader
// Creates a ripple wave effect emanating from the center of a plane
// The wave amplitude, frequency, and animation are controlled by uniforms

#version 330 core

// Input vertex attributes
layout(location = 0) in vec3 aPosition;  // Vertex position in model space
layout(location = 1) in vec4 aColor;     // Vertex color (used for distance info)

// Output to fragment shader
out vec4 vColor;           // Original vertex color
out float vDistFromCenter; // Distance from center (for gradient)
out float vHeight;         // Height offset (for wave coloring)
out vec3 vWorldPos;        // World position

// Uniform matrices for transformations
uniform mat4 uModel;       // Model matrix (local to world space)
uniform mat4 uView;        // View matrix (world to camera space)
uniform mat4 uProjection;  // Projection matrix (camera to clip space)

// Wave parameters
uniform float uTime;           // Animation time
uniform float uWaveAmplitude;  // Height of the wave
uniform float uWaveFrequency;  // Number of wave cycles
uniform float uPlaneRadius;    // Maximum distance from center (for dynamic falloff)

void main()
{
    // Calculate distance from center (0, 0) in XZ plane
    float distFromCenter = length(aPosition.xz);

    // Create a radial wave emanating from the center
    // The wave travels outward over time
    float wave = sin(distFromCenter * uWaveFrequency - uTime) * uWaveAmplitude;

    // Smooth the center to avoid pointy peak (flatten the very center naturally)
    // This simulates how real water droplets create a smooth initial displacement
    float centerSmoothing = smoothstep(0.0, 0.5, distFromCenter);
    wave *= centerSmoothing;

    // Apply gentle distance-based falloff only at far edges (dynamic based on plane size)
    // Starts fading at 90% of radius, fully faded at 106% of radius
    float falloffStart = uPlaneRadius * 0.90;
    float falloffEnd = uPlaneRadius * 1.06;
    float falloff = 1.0 - smoothstep(falloffStart, falloffEnd, distFromCenter);
    wave *= falloff;

    // Create modified position with wave displacement in Y axis
    vec3 displacedPosition = aPosition;
    displacedPosition.y += wave;

    // Pass data to fragment shader
    vColor = aColor;
    vDistFromCenter = distFromCenter;
    vHeight = wave;
    vWorldPos = vec3(uModel * vec4(displacedPosition, 1.0));

    // Transform vertex position: Model -> View -> Projection
    gl_Position = uProjection * uView * uModel * vec4(displacedPosition, 1.0);
}
