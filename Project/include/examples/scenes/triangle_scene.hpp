#pragma once

#include "scene/scene.hpp"
#include "graphics/mesh.hpp"
#include "graphics/shader.hpp"

namespace examples
{
    using namespace scene;
    using namespace graphics;

    class TriangleScene final : public Scene
    {
    public:
        // Constructor and Destructor
        TriangleScene();
        ~TriangleScene() override;

        // Scene lifecycle
        void OnCreate() override;
        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnDestroy() override;

    private:
        // Scene resources
        Mesh* m_TriangleMesh;
        Shader* m_Shader;

        // Mesh generation
        void CreateTriangle();
    };
}
