// Sphere Fragment Shader - Fresnel rim lighting with color gradients

#version 330 core

// Input from vertex shader
in vec3 vPosition;
in vec3 vNormal;
in vec4 vColor;
in vec2 vTexCoord;

// Output
out vec4 FragColor;

// Color uniforms
uniform vec4 uRimColor;
uniform vec4 uCoreColor;

// Animation uniforms
uniform vec3 uCameraPos;
uniform float uTime;
uniform float uPulseSpeed;

// Fresnel parameters
uniform float uRimPower;
uniform float uRimIntensity;

void main()
{
    // Normalize interpolated normal
    vec3 normal = normalize(vNormal);
    vec3 viewDir = normalize(uCameraPos - vPosition);

    // Calculate Fresnel effect (edges glow more than center)
    float fresnel = 1.0 - max(dot(normal, viewDir), 0.0);
    fresnel = pow(fresnel, uRimPower);

    // Create pulsing animation
    float pulse = 0.5 + 0.5 * sin(uTime * uPulseSpeed);

    // Blend core and rim colors based on Fresnel
    vec4 baseColor = mix(uCoreColor, uRimColor, fresnel);

    // Add animated pulse to rim
    baseColor.rgb += uRimColor.rgb * fresnel * pulse * 0.3 * uRimIntensity;

    // Blend with vertex color for subtle variation
    baseColor = mix(baseColor, vColor, 0.15);

    // Apply simple diffuse lighting
    vec3 lightDir = normalize(vec3(0.5, 1.0, 0.5));
    float diffuse = max(dot(normal, lightDir), 0.0) * 0.3 + 0.7;
    baseColor.rgb *= diffuse;

    // Add ambient light
    baseColor.rgb += vec3(0.1);

    // Add subtle rim highlight for depth
    float rim = pow(1.0 - max(dot(normal, viewDir), 0.0), 2.0) * 0.15;
    baseColor.rgb += vec3(rim);

    // Output final color
    FragColor = vec4(baseColor.rgb, 1.0);
}
