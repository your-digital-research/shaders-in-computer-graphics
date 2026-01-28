#include "scene/scene_manager.hpp"

#include <stdexcept>

#include "examples/scenes/cube_scene.hpp"
#include "examples/scenes/plane_scene.hpp"
#include "examples/scenes/quad_scene.hpp"
#include "examples/scenes/sphere_scene.hpp"
#include "examples/scenes/triangle_scene.hpp"

#include "platform/window.hpp"

namespace scene
{
    using namespace platform;
    using namespace examples;

    SceneManager::SceneManager(Window* window)
        : m_Window(window)
        , m_Camera(std::make_unique<Camera>())
    {
        if (!m_Window)
        {
            throw std::invalid_argument("Window pointer cannot be null!");
        }
    }

    void SceneManager::InitializeDefaultScenes()
    {
        auto triangleScene = std::make_unique<TriangleScene>(m_Camera.get());
        auto cubeScene = std::make_unique<CubeScene>(m_Camera.get());
        auto planeScene = std::make_unique<PlaneScene>(m_Camera.get());
        auto quadScene = std::make_unique<QuadScene>(m_Camera.get());
        auto sphereScene = std::make_unique<SphereScene>(m_Camera.get());

        AddScene("rainbow-triangle", std::move(triangleScene));
        AddScene("rotating-cube", std::move(cubeScene));
        AddScene("wavy-plane", std::move(planeScene));
        AddScene("uv-quad", std::move(quadScene));
        AddScene("fresnel-sphere", std::move(sphereScene));

        SetActiveScene("rainbow-triangle");
    }

    SceneManager::~SceneManager()
    {
        m_ActiveScene = nullptr;
        m_Scenes.clear();
    }

    void SceneManager::AddScene(const std::string& name, std::unique_ptr<Scene> scene)
    {
        scene->SetName(name);

        if (m_Scenes.find(name) != m_Scenes.end())
        {
            m_Scenes[name] = std::move(scene);

            if (m_ActiveScene == m_Scenes[name].get())
            {
                m_ActiveScene = scene.get();
            }
        }
        else
        {
            m_Scenes[name] = std::move(scene);

            if (m_ActiveScene == nullptr)
            {
                m_ActiveScene = m_Scenes[name].get();
            }
        }
    }

    void SceneManager::RemoveScene(const std::string& name)
    {
        if (const auto it = m_Scenes.find(name); it != m_Scenes.end())
        {
            if (m_ActiveScene == it->second.get())
            {
                m_ActiveScene = nullptr;
            }

            m_Scenes.erase(it);
        }
    }

    void SceneManager::SetActiveScene(const std::string& name)
    {
        if (const auto it = m_Scenes.find(name); it != m_Scenes.end())
        {
            m_ActiveScene = it->second.get();
            m_ActiveScene->ResetToDefault();
        }
    }

    std::string SceneManager::GetActiveSceneName() const
    {
        if (!m_ActiveScene) return "None";

        return m_ActiveScene->GetName();
    }

    void SceneManager::UpdateActiveScene(const float deltaTime) const
    {
        if (!m_ActiveScene) return;

        if (m_Camera)
        {
            m_Camera->UpdateAspectRatio(m_Window->GetAspectRatio());
        }

        m_ActiveScene->OnUpdate(deltaTime);
    }

    void SceneManager::RenderActiveScene() const
    {
        if (!m_ActiveScene) return;

        m_ActiveScene->OnRender();
    }
}
