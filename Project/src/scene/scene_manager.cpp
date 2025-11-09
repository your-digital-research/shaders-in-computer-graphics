#include "scene/scene_manager.hpp"

namespace scene
{
    SceneManager::SceneManager() : m_ActiveScene(nullptr)
    {
        //
    }

    SceneManager::~SceneManager()
    {
        m_ActiveScene = nullptr;
        m_Scenes.clear();
    }

    void SceneManager::AddScene(const std::string& name, std::unique_ptr<Scene> scene)
    {
        if (m_Scenes.find(name) != m_Scenes.end())
        {
            // Scene already exists, replace it
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
            m_Scenes[name] = std::move(scene);

            // If this is the first scene, make it active
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
            // If removing an active scene, set active to nullptr
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
        }
    }

    void SceneManager::UpdateActiveScene(float deltaTime)
    {
        if (!m_ActiveScene) return;

        m_ActiveScene->OnUpdate(deltaTime);
    }

    void SceneManager::RenderActiveScene()
    {
        if (!m_ActiveScene) return;

        m_ActiveScene->OnRender();
    }
}
