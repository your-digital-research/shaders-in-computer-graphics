#pragma once

#include "scene/scene.hpp"
#include "graphics/mesh.hpp"
#include "graphics/shader.hpp"

namespace scene
{
    class CubeScene : public Scene
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
        graphics::Mesh* m_CubeMesh;
        graphics::Shader* m_Shader;

        // Transform matrices
        glm::mat4 m_ModelMatrix;
        float m_RotationAngle;
    };
}
