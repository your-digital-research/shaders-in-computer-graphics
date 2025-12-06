#pragma once

#include "scene/scene.hpp"
#include "graphics/mesh.hpp"
#include "graphics/shader.hpp"

namespace examples
{
    using namespace glm;
    using namespace scene;
    using namespace graphics;

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
        float m_RotationAngle;

        // Mesh generation
        void CreateCube();
    };
}
