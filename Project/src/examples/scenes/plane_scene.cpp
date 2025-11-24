#include <vector>
#include <cmath>

#include <glm/gtc/matrix_transform.hpp>

#include "view/camera.hpp"
#include "graphics/types.hpp"
#include "examples/scenes/plane_scene.hpp"

namespace examples
{
    using namespace std;
    using namespace glm;
    using namespace graphics;

    PlaneScene::PlaneScene()
        : m_PlaneMesh(nullptr),
          m_Shader(nullptr),
          m_WaveCount(8),
          m_Time(0.0f),
          m_WaveSpeed(5.0f),
          m_WaveAmplitude(0.25f),
          m_WaveFrequency(3.14159f),
          m_OpacityFadeStart(0.5f),
          m_GridSize(128),
          m_PlaneSize(8.0f),
          m_PlaneRadius(0.0f),
          m_CurrentGradient(GradientTheme::NeonCyberpunk)
    {
        SetGradientTheme(m_CurrentGradient);

        PlaneScene::OnCreate();
    }

    PlaneScene::~PlaneScene()
    {
        PlaneScene::OnDestroy();
    }

    void PlaneScene::CreateTessellatedPlane(const int gridSize, const float planeSize)
    {
        Vertices vertices;
        VertexIndices indices;

        const float stepSize = planeSize / static_cast<float>(gridSize);
        const float halfSize = planeSize * 0.5f;

        // Generate vertices
        for (int z = 0; z <= gridSize; ++z)
        {
            for (int x = 0; x <= gridSize; ++x)
            {
                const float xPos = static_cast<float>(x) * stepSize - halfSize;
                const float zPos = static_cast<float>(z) * stepSize - halfSize;

                // Calculate distance from a center for color variation
                const float distFromCenter = sqrt(xPos * xPos + zPos * zPos);
                const float normalizedDist = distFromCenter / (halfSize * 1.414f); // Normalize to [0, 1]

                // Create a color based on distance (will be used for interpolation)
                const auto color = Color(normalizedDist, 0.5f, 1.0f - normalizedDist, 1.0f);

                vertices.emplace_back(vec3(xPos, 0.0f, zPos), color);
            }
        }

        // Generate indices for triangles
        for (int z = 0; z < gridSize; ++z)
        {
            for (int x = 0; x < gridSize; ++x)
            {
                const int topLeft = z * (gridSize + 1) + x;
                const int topRight = topLeft + 1;
                const int bottomLeft = (z + 1) * (gridSize + 1) + x;
                const int bottomRight = bottomLeft + 1;

                // First triangle
                indices.push_back(topLeft);
                indices.push_back(bottomLeft);
                indices.push_back(topRight);

                // Second triangle
                indices.push_back(topRight);
                indices.push_back(bottomLeft);
                indices.push_back(bottomRight);
            }
        }

        m_PlaneMesh = new Mesh(vertices, indices);
    }

    void PlaneScene::OnCreate()
    {
        // Create a highly tessellated plane for very smooth water ripples
        CreateTessellatedPlane(m_GridSize, m_PlaneSize);

        // Calculate plane radius (half diagonal from center to corner)
        // For a square plane of size S, diagonal = S * sqrt(2), half diagonal = S * sqrt(2) / 2
        m_PlaneRadius = m_PlaneSize * 0.70710678118f; // sqrt(2)/2 ≈ 0.707

        // Create a shader for wave effect
        m_Shader = new Shader("shaders/wave/vertex.glsl", "shaders/wave/fragment.glsl");

        // Calculate initial frequency based on wave count and plane size
        // We want m_WaveCount full wavelengths to fit in the radius
        // Check if it's a default value
        if (m_WaveFrequency == 3.14159f)
        {
            m_WaveFrequency = (static_cast<float>(m_WaveCount) * 2.0f * 3.14159f) / m_PlaneRadius;
        }

        // Setup camera - position it at an angle for better wave visibility
        m_Camera->SetPosition(vec3(0.0f, 7.5f, 8.25f));
        m_Camera->SetRotationEuler(vec3(-90.0f, -45.0f, 0.0f));
        m_Camera->SetProjection(45.0f, 1.0f, 0.1f, 100.0f);
    }

    void PlaneScene::OnUpdate(const float deltaTime)
    {
        // Update time for wave animation
        m_Time += deltaTime * m_WaveSpeed;
    }

    void PlaneScene::OnRender()
    {
        // Bind shader and set uniforms
        m_Shader->Bind();
        m_Shader->SetMat4("uModel", mat4(1.0f));
        m_Shader->SetMat4("uView", m_Camera->GetViewMatrix());
        m_Shader->SetMat4("uProjection", m_Camera->GetProjectionMatrix());

        // Set wave parameters
        m_Shader->SetFloat("uTime", m_Time);
        m_Shader->SetFloat("uWaveAmplitude", m_WaveAmplitude);
        m_Shader->SetFloat("uWaveFrequency", m_WaveFrequency);
        m_Shader->SetFloat("uOpacityFadeStart", m_OpacityFadeStart);
        m_Shader->SetFloat("uPlaneRadius", m_PlaneRadius);

        m_Shader->SetVec4("uCenterColor", m_CenterColor.ToVec4());
        m_Shader->SetVec4("uEdgeColor", m_EdgeColor.ToVec4());
        m_Shader->SetVec4("uWavePeakColor", m_WavePeakColor.ToVec4());
        m_Shader->SetVec4("uWaveTroughColor", m_WaveTroughColor.ToVec4());

        // Enable blending for transparency
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // Render plane
        m_PlaneMesh->Bind();
        m_PlaneMesh->Draw();

        Mesh::Unbind();
        Shader::Unbind();

        // Disable blending
        glDisable(GL_BLEND);
    }

    void PlaneScene::OnDestroy()
    {
        delete m_PlaneMesh;
        delete m_Shader;

        m_PlaneMesh = nullptr;
        m_Shader = nullptr;
    }

    void PlaneScene::SetGradientTheme(const GradientTheme theme)
    {
        m_CurrentGradient = theme;

        switch (theme)
        {
            case GradientTheme::Unknown:
                m_CenterColor = Color::White;
                m_EdgeColor = Color::White;
                m_WavePeakColor = Color::White;
                m_WaveTroughColor = Color::White;
                break;

            case GradientTheme::AuroraSunset:
                m_CenterColor = Color::RGB(0.6f, 0.2f, 0.8f);           // Deep purple
                m_EdgeColor = Color::RGB(1.0f, 0.6f, 0.3f);             // Warm orange
                m_WavePeakColor = Color::RGB(1.0f, 0.9f, 0.4f);         // Golden yellow
                m_WaveTroughColor = Color::RGB(0.4f, 0.15f, 0.6f);      // Dark purple
                break;

            case GradientTheme::NeonCyberpunk:
                m_CenterColor = Color::RGB(1.0f, 0.0f, 0.8f);           // Hot magenta
                m_EdgeColor = Color::RGB(0.0f, 0.9f, 1.0f);             // Bright cyan
                m_WavePeakColor = Color::RGB(1.0f, 1.0f, 1.0f);         // Pure white
                m_WaveTroughColor = Color::RGB(0.4f, 0.0f, 0.6f);       // Deep magenta
                break;

            case GradientTheme::OceanDepth:
                m_CenterColor = Color::RGB(0.0f, 0.3f, 0.6f);           // Deep ocean blue
                m_EdgeColor = Color::RGB(0.2f, 0.9f, 0.9f);             // Bright turquoise
                m_WavePeakColor = Color::RGB(0.7f, 1.0f, 1.0f);         // Light aqua foam
                m_WaveTroughColor = Color::RGB(0.0f, 0.2f, 0.4f);       // Dark navy
                break;

            case GradientTheme::FireLava:
                m_CenterColor = Color::RGB(0.8f, 0.1f, 0.0f);           // Deep red
                m_EdgeColor = Color::RGB(1.0f, 0.8f, 0.0f);             // Bright yellow
                m_WavePeakColor = Color::RGB(1.0f, 1.0f, 0.8f);         // White hot
                m_WaveTroughColor = Color::RGB(0.5f, 0.0f, 0.0f);       // Dark crimson
                break;

            case GradientTheme::MintRose:
                m_CenterColor = Color::RGB(1.0f, 0.4f, 0.7f);           // Soft rose pink
                m_EdgeColor = Color::RGB(0.4f, 1.0f, 0.8f);             // Mint green
                m_WavePeakColor = Color::RGB(1.0f, 0.95f, 0.85f);       // Cream white
                m_WaveTroughColor = Color::RGB(0.7f, 0.2f, 0.5f);       // Deep rose
                break;

            case GradientTheme::ToxicGreen:
                m_CenterColor = Color::RGB(0.2f, 0.8f, 0.1f);           // Bright lime
                m_EdgeColor = Color::RGB(0.8f, 1.0f, 0.0f);             // Neon yellow-green
                m_WavePeakColor = Color::RGB(0.9f, 1.0f, 0.7f);         // Light lime
                m_WaveTroughColor = Color::RGB(0.1f, 0.4f, 0.0f);       // Dark forest green
                break;

            case GradientTheme::RoyalPurpleGold:
                m_CenterColor = Color::RGB(0.5f, 0.1f, 0.8f);           // Royal purple
                m_EdgeColor = Color::RGB(1.0f, 0.85f, 0.2f);            // Rich gold
                m_WavePeakColor = Color::RGB(1.0f, 0.95f, 0.6f);        // Light gold
                m_WaveTroughColor = Color::RGB(0.3f, 0.05f, 0.5f);      // Deep violet
                break;

            case GradientTheme::CottonCandy:
                m_CenterColor = Color::RGB(1.0f, 0.6f, 0.9f);           // Pink
                m_EdgeColor = Color::RGB(0.6f, 0.8f, 1.0f);             // Baby blue
                m_WavePeakColor = Color::RGB(1.0f, 0.95f, 1.0f);        // Almost white
                m_WaveTroughColor = Color::RGB(0.8f, 0.4f, 0.7f);       // Mauve
                break;

            case GradientTheme::ElectricStorm:
                m_CenterColor = Color::RGB(0.1f, 0.1f, 0.9f);           // Electric blue
                m_EdgeColor = Color::RGB(0.9f, 0.9f, 1.0f);             // Bright white-blue
                m_WavePeakColor = Color::RGB(1.0f, 1.0f, 0.7f);         // Lightning yellow
                m_WaveTroughColor = Color::RGB(0.05f, 0.0f, 0.5f);      // Deep indigo
                break;

            case GradientTheme::PeachSunset:
                m_CenterColor = Color::RGB(1.0f, 0.5f, 0.3f);           // Coral peach
                m_EdgeColor = Color::RGB(1.0f, 0.9f, 0.5f);             // Soft yellow
                m_WavePeakColor = Color::RGB(1.0f, 0.95f, 0.8f);        // Cream
                m_WaveTroughColor = Color::RGB(0.8f, 0.3f, 0.2f);       // Deep orange
                break;

            case GradientTheme::MatrixGreen:
                m_CenterColor = Color::RGB(0.0f, 0.8f, 0.3f);           // Matrix green
                m_EdgeColor = Color::RGB(0.5f, 1.0f, 0.6f);             // Light green
                m_WavePeakColor = Color::RGB(0.8f, 1.0f, 0.9f);         // Mint white
                m_WaveTroughColor = Color::RGB(0.0f, 0.4f, 0.1f);       // Dark emerald
                break;
        }
    }
}
