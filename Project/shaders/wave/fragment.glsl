// Wave Fragment Shader - Radial gradient with wave-based coloring

#version 330 core

// Input from vertex shader
in vec4 vColor;
in float vDistFromCenter;
in float vHeight;
in vec3 vWorldPos;

// Output
out vec4 FragColor;

// Color uniforms
uniform vec4 uCenterColor;
uniform vec4 uEdgeColor;
uniform vec4 uWavePeakColor;
uniform vec4 uWaveTroughColor;

// Wave parameters
uniform float uOpacityFadeStart;
uniform float uPlaneRadius;

void main()
{
    // Normalize distance from center
    float normalizedDist = clamp(vDistFromCenter / uPlaneRadius, 0.0, 1.0);

    // Calculate edge transparency fade
    float fadeStart = uOpacityFadeStart;
    float fadeEnd = min(fadeStart + 0.2, 1.0);
    float alpha = 1.0 - smoothstep(fadeStart, fadeEnd, normalizedDist);

    // Create radial gradient from center to edge
    vec4 baseColor = mix(uCenterColor, uEdgeColor, smoothstep(0.0, 1.0, normalizedDist));

    // Blend wave colors based on height (peaks vs troughs)
    float normalizedHeight = clamp(vHeight * 3.0 + 0.5, 0.0, 1.0);
    vec4 waveColor = mix(uWaveTroughColor, uWavePeakColor, normalizedHeight);

    float waveInfluence = clamp(abs(vHeight) * 3.5, 0.0, 0.85);
    vec4 finalColor = mix(baseColor, waveColor, waveInfluence);

    // Add specular highlight on wave peaks
    float specular = smoothstep(0.1, 0.3, vHeight) * 0.5;
    finalColor.rgb += vec3(specular);

    // Add ambient occlusion in troughs
    float ao = smoothstep(-0.15, 0.0, vHeight);
    finalColor.rgb *= 0.85 + 0.15 * ao;

    // Add rim lighting for depth perception
    float rim = pow(1.0 - normalizedDist, 4.0) * 0.2;
    finalColor.rgb += vec3(rim * 0.6, rim * 0.9, rim * 1.0);

    // Output final color with transparency
    FragColor = vec4(finalColor.rgb, alpha);
}
