#pragma once

#include "scene/scene.hpp"
#include "graphics/mesh.hpp"
#include "graphics/shader.hpp"

namespace examples
{
    using namespace scene;
    using namespace graphics;

    class TriangleRainbowScene final : public Scene
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
        Mesh* m_TriangleMesh;
        Shader* m_Shader;
    };
}
