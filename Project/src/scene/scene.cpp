#include "scene/scene.hpp"

namespace scene
{
    using namespace view;

    Scene::Scene() : m_Camera(nullptr)
    {
        m_Camera = new Camera();
    }
}
