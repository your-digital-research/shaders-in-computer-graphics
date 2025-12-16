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
        TriangleScene();
        ~TriangleScene() override;

        void OnCreate() override;
        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnDestroy() override;

    private:
        Mesh* m_TriangleMesh;
        Shader* m_Shader;

        mat4 m_ModelMatrix;

        float m_TriangleSize;

        Color m_TopColor;
        Color m_BottomLeftColor;
        Color m_BottomRightColor;

        void CreateTriangle();
    };
}
