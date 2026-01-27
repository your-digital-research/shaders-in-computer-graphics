#include "scene/scene.hpp"

namespace scene
{
    using namespace view;

    Scene::Scene()
    {
        m_Camera = new Camera();
    }
}
