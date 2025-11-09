#pragma once

#include "scene/scene.hpp"
#include "graphics/mesh.hpp"
#include "graphics/shader.hpp"

namespace examples
{
    class TriangleRainbowScene final : public scene::Scene
    {
    public:
        // Constructor and Destructor
        TriangleRainbowScene();
        ~TriangleRainbowScene() override;

        // Scene lifecycle
        void OnCreate() override;
        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnDestroy() override;

    private:
        // Scene resources
        graphics::Mesh *m_TriangleMesh;
        graphics::Shader *m_Shader;
    };
}
