#include "scene/scene.hpp"
#include "view/camera.hpp"

namespace scene
{
    using namespace view;

    Scene::Scene() : m_Camera(nullptr)
    {
        m_Camera = new Camera();
    }
}
