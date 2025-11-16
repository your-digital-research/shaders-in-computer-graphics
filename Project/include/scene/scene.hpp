#pragma once

#include "graphics/shader.hpp"
#include "graphics/mesh.hpp"
#include "view/camera.hpp"

namespace scene
{
    using namespace view;

    class Scene
    {
    public:
        // Constructor and Destructor
        Scene();
        virtual ~Scene() = default;

        // Scene lifecycle
        virtual void OnCreate() = 0;
        virtual void OnUpdate(float deltaTime) = 0;
        virtual void OnRender() = 0;
        virtual void OnDestroy() = 0;

        // Viewport handling
        void UpdateAspectRatio(const float aspect) const
        {
            if (m_Camera) m_Camera->UpdateAspectRatio(aspect);
        }

    protected:
        // Scene components
        Camera* m_Camera;
    };
}
