#include "platform/window.hpp"
#include "scene/scene_manager.hpp"

#include "examples/scenes/triangle_scene.hpp"
#include "examples/scenes/cube_scene.hpp"
#include "examples/scenes/plane_scene.hpp"
#include "examples/scenes/quad_scene.hpp"
#include "examples/scenes/sphere_scene.hpp"

namespace scene
{
    using namespace std;
    using namespace platform;
    using namespace examples;

    SceneManager::SceneManager(Window* window)
        : m_Window(window),
          m_ActiveScene(nullptr)
    {
        //
    }

    void SceneManager::InitializeDefaultScenes()
    {
        // Create default scenes
        auto triangleScene = make_unique<TriangleScene>();
        auto cubeScene = make_unique<CubeScene>();
        auto planeScene = make_unique<PlaneScene>();
        auto quadScene = make_unique<QuadScene>();
        auto sphereScene = make_unique<SphereScene>();

        // Add scenes to the manager
        // NOTE: std::move explicitly qualified (best practice for move semantics)
        AddScene("rainbow-triangle", std::move(triangleScene));
        AddScene("rotating-cube", std::move(cubeScene));
        AddScene("wavy-plane", std::move(planeScene));
        AddScene("uv-quad", std::move(quadScene));
        AddScene("fresnel-sphere", std::move(sphereScene));

        // Set the default active scene
        SetActiveScene("rainbow-triangle");
    }

    SceneManager::~SceneManager()
    {
        m_ActiveScene = nullptr;
        m_Scenes.clear();
    }

    void SceneManager::AddScene(const string& name, unique_ptr<Scene> scene)
    {
        scene->SetName(name);

        if (m_Scenes.find(name) != m_Scenes.end())
        {
            // Scene already exists, replace it
            // NOTE: std::move explicitly qualified (best practice for move semantics)
            m_Scenes[name] = std::move(scene);

            // Update the active scene pointer if it was the one we replaced
            if (m_ActiveScene == m_Scenes[name].get())
            {
                m_ActiveScene = scene.get();
            }
        }
        else
        {
            // Add a new scene
            // NOTE: std::move explicitly qualified (best practice for move semantics)
            m_Scenes[name] = std::move(scene);

            // If this is the first scene, make it active
            if (m_ActiveScene == nullptr)
            {
                m_ActiveScene = m_Scenes[name].get();
            }
        }
    }

    void SceneManager::RemoveScene(const string& name)
    {
        if (const auto it = m_Scenes.find(name); it != m_Scenes.end())
        {
            // If removing an active scene, set active to nullptr
            if (m_ActiveScene == it->second.get())
            {
                m_ActiveScene = nullptr;
            }

            m_Scenes.erase(it);
        }
    }

    void SceneManager::SetActiveScene(const string& name)
    {
        if (const auto it = m_Scenes.find(name); it != m_Scenes.end())
        {
            m_ActiveScene = it->second.get();
        }
    }

    string SceneManager::GetActiveSceneName() const
    {
        if (!m_ActiveScene) return "None";

        return m_ActiveScene->GetName();
    }

    void SceneManager::UpdateActiveScene(const float deltaTime) const
    {
        if (!m_ActiveScene) return;

        // Update aspect ratio first
        m_ActiveScene->UpdateAspectRatio(m_Window->GetAspectRatio());

        // Then update scene logic
        m_ActiveScene->OnUpdate(deltaTime);
    }

    void SceneManager::RenderActiveScene() const
    {
        if (!m_ActiveScene) return;

        m_ActiveScene->OnRender();
    }
}
