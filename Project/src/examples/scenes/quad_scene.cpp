#include "examples/scenes/quad_scene.hpp"

#include <vector>

#include "imgui.h"

#include "constants/paths.hpp"
#include "graphics/types.hpp"

namespace examples
{
    QuadScene::QuadScene()
        : m_QuadMesh(nullptr),
          m_Shader(nullptr),
          m_ModelMatrix(1.0f),
          m_QuadWidth(1.0f),
          m_QuadHeight(1.0f),
          m_QuadColor(Color::White),
          m_DefaultQuadWidth(1.0f),
          m_DefaultQuadHeight(1.0f),
          m_DefaultCameraPosition(0.0f, 0.0f, 2.5f),
          m_DefaultCameraRotation(0.0f, 0.0f, 0.0f)
    {
        QuadScene::OnCreate();
    }

    QuadScene::~QuadScene()
    {
        QuadScene::OnDestroy();
    }

    void QuadScene::CreateQuad()
    {
        if (m_QuadMesh != nullptr)
        {
            delete m_QuadMesh;

            m_QuadMesh = nullptr;
        }

        const float halfWidth = m_QuadWidth * 0.5f;
        const float halfHeight = m_QuadHeight * 0.5f;

        const Vertices vertices = {
            Vertex(glm::vec3(-halfWidth, -halfHeight, 0.0f), m_QuadColor, glm::vec2(0.0f, 0.0f)),
            Vertex(glm::vec3(halfWidth, -halfHeight, 0.0f), m_QuadColor, glm::vec2(1.0f, 0.0f)),
            Vertex(glm::vec3(halfWidth, halfHeight, 0.0f), m_QuadColor, glm::vec2(1.0f, 1.0f)),
            Vertex(glm::vec3(-halfWidth, halfHeight, 0.0f), m_QuadColor, glm::vec2(0.0f, 1.0f)),
        };

        const VertexIndices indices = {
            0, 1, 2,
            0, 2, 3
        };

        m_QuadMesh = new Mesh(vertices, indices);
    }

    void QuadScene::OnCreate()
    {
        CreateQuad();

        m_Shader = new Shader(constants::paths::UV_VERTEX_SHADER,
                              constants::paths::UV_FRAGMENT_SHADER);

        m_Camera->SetPosition(glm::vec3(0.0f, 0.0f, 2.5f));
    }

    void QuadScene::OnUpdate(float deltaTime)
    {
        //
    }

    void QuadScene::OnRender()
    {
        m_Shader->Bind();

        m_Shader->SetMat4("uModel", m_ModelMatrix);
        m_Shader->SetMat4("uView", m_Camera->GetViewMatrix());
        m_Shader->SetMat4("uProjection", m_Camera->GetProjectionMatrix());

        m_QuadMesh->Bind();
        m_QuadMesh->Draw();

        Mesh::Unbind();
        Shader::Unbind();
    }

    void QuadScene::OnDestroy()
    {
        delete m_QuadMesh;
        delete m_Shader;

        m_QuadMesh = nullptr;
        m_Shader = nullptr;
    }

    void QuadScene::SetQuadWidth(const float width)
    {
        m_QuadWidth = glm::max(0.1f, width);

        CreateQuad();
    }

    void QuadScene::SetQuadHeight(const float height)
    {
        m_QuadHeight = glm::max(0.1f, height);

        CreateQuad();
    }

    void QuadScene::RenderSettings()
    {
        constexpr float panelWidth = 340.0f;
        constexpr float panelHeight = 180.0f;
        constexpr float padding = 10.0f;

        const ImGuiIO& io = ImGui::GetIO();
        const float xPos = io.DisplaySize.x - panelWidth - padding;
        const float yPos = io.DisplaySize.y - panelHeight - padding;

        ImGui::SetNextWindowPos(ImVec2(xPos, yPos), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(panelWidth, panelHeight), ImGuiCond_Always);

        ImGui::Begin("Scene Settings", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);

        ImGui::Text("Quad Properties");
        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        // Quad Width
        float quadWidth = m_QuadWidth;
        if (ImGui::SliderFloat("Width", &quadWidth, 0.1f, 5.0f, "%.2f"))
        {
            SetQuadWidth(quadWidth);
        }

        // Quad Height
        float quadHeight = m_QuadHeight;
        if (ImGui::SliderFloat("Height", &quadHeight, 0.1f, 5.0f, "%.2f"))
        {
            SetQuadHeight(quadHeight);
        }

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        constexpr float buttonHeight = 30.0f;
        if (const float availableHeight = ImGui::GetContentRegionAvail().y; availableHeight > buttonHeight)
        {
            ImGui::Dummy(ImVec2(0.0f, availableHeight - buttonHeight));
        }

        // ImGui::Separator();

        if (ImGui::Button("Reset to Default", ImVec2(-1, 0)))
        {
            ResetToDefault();
        }

        ImGui::End();
    }

    void QuadScene::ResetToDefault()
    {
        m_QuadWidth = m_DefaultQuadWidth;
        m_QuadHeight = m_DefaultQuadHeight;

        m_Camera->SetPosition(m_DefaultCameraPosition);
        m_Camera->SetRotationEuler(m_DefaultCameraRotation);

        CreateQuad();
    }
}
