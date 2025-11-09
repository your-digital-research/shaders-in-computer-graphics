#include "scene/scene.hpp"

namespace scene
{
    Scene::Scene() : m_Camera(nullptr)
    {
        m_Camera = new view::Camera();
    }
}
