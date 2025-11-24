// Wave Plane Fragment Shader
// Colors the plane with a radial gradient from center
// Wave peaks and troughs are colored differently

#version 330 core

// Input from vertex shader
in vec4 vColor;                 // Original vertex color
in float vDistFromCenter;       // Distance from center
in float vHeight;               // Height displacement from wave
in vec3 vWorldPos;              // World position

// Output color
out vec4 FragColor;

// Color parameters
uniform vec3 uCenterColor;      // Color at the center of the plane
uniform vec3 uEdgeColor;        // Color at the edges of the plane
uniform vec3 uWavePeakColor;    // Color for wave peaks (high points)
uniform vec3 uWaveTroughColor;  // Color for wave troughs (low points)

// Normalized distance [0..1] where opacity fading starts (0 = only center visible, 1 = fully opaque)
uniform float uOpacityFadeStart;

// Maximum distance from center to edge (half diagonal)
uniform float uPlaneRadius;

void main()
{
    // Normalize distance for gradient based on actual plane radius
    float normalizedDist = clamp(vDistFromCenter / uPlaneRadius, 0.0, 1.0);

    // Calculate alpha based on distance - edges fade out to transparent
    // When uOpacityFadeStart = 0.0, only center is visible (edges fully transparent)
    // When uOpacityFadeStart = 1.0, entire plane is opaque (no transparency)
    float fadeStart = uOpacityFadeStart;
    float fadeEnd = min(fadeStart + 0.2, 1.0); // 20% fade zone
    float alpha = 1.0 - smoothstep(fadeStart, fadeEnd, normalizedDist);

    // Create smooth radial gradient from center to edge (deeper in center)
    vec3 baseColor = mix(uCenterColor, uEdgeColor, smoothstep(0.0, 1.0, normalizedDist));

    // Normalize height to [0, 1] range for color mixing
    // Positive height = peak (toward 1), negative height = trough (toward 0)
    float normalizedHeight = vHeight * 3.0 + 0.5; // Increased multiplier for more contrast
    normalizedHeight = clamp(normalizedHeight, 0.0, 1.0);

    // Mix between trough and peak colors based on height
    vec3 waveColor = mix(uWaveTroughColor, uWavePeakColor, normalizedHeight);

    // Blend the base gradient with wave coloring
    // Stronger influence for more visible ripples
    float waveInfluence = abs(vHeight) * 3.5;
    waveInfluence = clamp(waveInfluence, 0.0, 0.85);

    vec3 finalColor = mix(baseColor, waveColor, waveInfluence);

    // Add specular highlight on wave peaks (simulates light reflection)
    float specular = smoothstep(0.1, 0.3, vHeight) * 0.5;
    finalColor += vec3(specular);

    // Add very gentle shading in troughs
    float ao = smoothstep(-0.15, 0.0, vHeight);
    finalColor *= 0.85 + 0.15 * ao;

    // Add cheerful rim lighting for depth perception
    float rim = pow(1.0 - normalizedDist, 4.0) * 0.2;
    finalColor += vec3(rim * 0.6, rim * 0.9, rim * 1.0);

    // Output final color with calculated alpha (transparent at edges)
    FragColor = vec4(finalColor, alpha);
}
