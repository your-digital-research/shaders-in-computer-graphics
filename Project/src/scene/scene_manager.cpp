#include "platform/window.hpp"
#include "scene/scene_manager.hpp"
#include "examples/scenes/cube_scene.hpp"
#include "examples/scenes/triangle_rainbow_scene.hpp"

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
        auto cubeScene = make_unique<CubeScene>();
        auto triangleScene = make_unique<TriangleRainbowScene>();

        // Add scenes to the manager
        // NOTE: std::move explicitly qualified (best practice for move semantics)
        AddScene("cube", std::move(cubeScene));
        AddScene("triangle", std::move(triangleScene));

        // Set the default active scene
        SetActiveScene("triangle");
    }

    SceneManager::~SceneManager()
    {
        m_ActiveScene = nullptr;
        m_Scenes.clear();
    }

    void SceneManager::AddScene(const string& name, unique_ptr<Scene> scene)
    {
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
