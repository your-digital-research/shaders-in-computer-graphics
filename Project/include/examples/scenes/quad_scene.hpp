#pragma once

#include "scene/scene.hpp"
#include "graphics/mesh.hpp"
#include "graphics/shader.hpp"

namespace examples
{
    using namespace scene;
    using namespace graphics;

    class QuadScene final : public Scene
    {
    public:
        QuadScene();
        ~QuadScene() override;

        void OnCreate() override;
        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnDestroy() override;

    private:
        Mesh* m_QuadMesh;
        Shader* m_Shader;

        glm::mat4 m_ModelMatrix;

        float m_QuadWidth;
        float m_QuadHeight;
        Color m_QuadColor;

        void CreateQuad();
    };
}
