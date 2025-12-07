#pragma once

#include "scene/scene.hpp"
#include "graphics/mesh.hpp"
#include "graphics/shader.hpp"

namespace examples
{
    using namespace glm;
    using namespace scene;
    using namespace graphics;

    // Color theme options for cube faces
    enum class CubeColorTheme
    {
        Unknown,
        PastelDream,       // Soft pastel colors
        NeonCyberpunk,     // Bright neon colors
        OceanDepth,        // Blues and teals
        SunsetVibes,       // Warm oranges and pinks
        ForestNature,      // Greens and browns
        RoyalLuxury,       // Purples and golds
        FireAndIce,        // Reds and blues contrast
        CandyPop,          // Bright candy colors
        MonochromeGray,    // Grayscale
        RainbowSpectrum    // Full rainbow colors
    };

    class CubeScene final : public Scene
    {
    public:
        // Constructor and Destructor
        CubeScene();
        ~CubeScene() override;

        // Scene lifecycle
        void OnCreate() override;
        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnDestroy() override;

    private:
        // Scene resources
        Mesh* m_CubeMesh;
        Shader* m_Shader;

        // Transform matrices
        mat4 m_ModelMatrix;

        // Animation parameters
        float m_RotationAngle;
        float m_RotationSpeed;
        vec3 m_RotationAxis;

        // Cube properties
        float m_CubeSize;

        // Colors
        Color m_FrontColor = Color::White;
        Color m_BackColor = Color::White;
        Color m_RightColor = Color::White;
        Color m_LeftColor = Color::White;
        Color m_TopColor = Color::White;
        Color m_BottomColor = Color::White;
        CubeColorTheme m_CurrentColorTheme = CubeColorTheme::Unknown;

        // Mesh generation
        void CreateCube();

        // Color management
        void SetColorTheme(CubeColorTheme theme);
    };
}
