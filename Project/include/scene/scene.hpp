#pragma once

#include "scene/camera.hpp"
#include "graphics/shader.hpp"
#include "graphics/mesh.hpp"

namespace scene
{
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

    protected:
        // Scene components
        Camera *m_Camera;
    };
}
