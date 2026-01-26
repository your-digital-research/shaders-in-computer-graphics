#include <vector>

#include "imgui.h"

#include "constants/paths.hpp"
#include "examples/scenes/triangle_scene.hpp"
#include "graphics/types.hpp"
#include "view/camera.hpp"

namespace examples
{
    using namespace std;
    using namespace glm;

    TriangleScene::TriangleScene()
        : m_TriangleMesh(nullptr),
          m_Shader(nullptr),
          m_ModelMatrix(1.0f),
          m_TriangleSize(1.0f),
          m_DefaultTriangleSize(1.0f),
          m_TopColor(Color::Red),
          m_BottomLeftColor(Color::Green),
          m_BottomRightColor(Color::Blue),
          m_DefaultTopColor(Color::Red),
          m_DefaultBottomLeftColor(Color::Green),
          m_DefaultBottomRightColor(Color::Blue),
          m_TopPosition(0.0f, 0.5f, 0.0f),
          m_BottomLeftPosition(-0.5f, -0.5f, 0.0f),
          m_BottomRightPosition(0.5f, -0.5f, 0.0f),
          m_DefaultTopPosition(0.0f, 0.5f, 0.0f),
          m_DefaultBottomLeftPosition(-0.5f, -0.5f, 0.0f),
          m_DefaultBottomRightPosition(0.5f, -0.5f, 0.0f),
          m_BaseTopPosition(0.0f, 0.5f, 0.0f),
          m_BaseBottomLeftPosition(-0.5f, -0.5f, 0.0f),
          m_BaseBottomRightPosition(0.5f, -0.5f, 0.0f),
          m_DefaultCameraPosition(0.0f, 0.0f, 2.5f),
          m_DefaultCameraRotation(0.0f, 0.0f, 0.0f)
    {
        TriangleScene::OnCreate();
    }

    TriangleScene::~TriangleScene()
    {
        TriangleScene::OnDestroy();
    }

    void TriangleScene::CreateTriangle()
    {
        if (m_TriangleMesh != nullptr)
        {
            delete m_TriangleMesh;

            m_TriangleMesh = nullptr;
        }

        const Vertices vertices = {
            Vertex(m_TopPosition, m_TopColor, vec2(0.5f, 1.0f)),
            Vertex(m_BottomLeftPosition, m_BottomLeftColor, vec2(0.0f, 0.0f)),
            Vertex(m_BottomRightPosition, m_BottomRightColor, vec2(1.0f, 0.0f))
        };

        const VertexIndices indices = {0, 1, 2};

        m_TriangleMesh = new Mesh(vertices, indices);
    }

    void TriangleScene::OnCreate()
    {
        CreateTriangle();

        m_Shader = new Shader(constants::paths::COLORED_VERTEX_SHADER,
                              constants::paths::COLORED_FRAGMENT_SHADER);

        m_Camera->SetPosition(vec3(0.0f, 0.0f, 2.5f));
    }

    void TriangleScene::OnUpdate(float deltaTime)
    {
        //
    }

    void TriangleScene::OnRender()
    {
        m_Shader->Bind();

        m_Shader->SetMat4("uModel", m_ModelMatrix);
        m_Shader->SetMat4("uView", m_Camera->GetViewMatrix());
        m_Shader->SetMat4("uProjection", m_Camera->GetProjectionMatrix());

        m_TriangleMesh->Bind();
        m_TriangleMesh->Draw();

        Mesh::Unbind();
        Shader::Unbind();
    }

    void TriangleScene::OnDestroy()
    {
        delete m_TriangleMesh;
        delete m_Shader;

        m_TriangleMesh = nullptr;
        m_Shader = nullptr;
    }

    void TriangleScene::SetTopColor(const Color& color)
    {
        m_TopColor = color;

        CreateTriangle();
    }

    void TriangleScene::SetBottomLeftColor(const Color& color)
    {
        m_BottomLeftColor = color;

        CreateTriangle();
    }

    void TriangleScene::SetBottomRightColor(const Color& color)
    {
        m_BottomRightColor = color;

        CreateTriangle();
    }

    void TriangleScene::SetTriangleSize(float size)
    {
        m_TriangleSize = glm::max(0.1f, size);

        // Scale the vertex positions from base positions based on size
        m_TopPosition = m_BaseTopPosition * m_TriangleSize;
        m_BottomLeftPosition = m_BaseBottomLeftPosition * m_TriangleSize;
        m_BottomRightPosition = m_BaseBottomRightPosition * m_TriangleSize;

        CreateTriangle();
    }

    void TriangleScene::SetTopPosition(const vec3& position)
    {
        m_TopPosition = position;
        m_BaseTopPosition = position / m_TriangleSize;

        CreateTriangle();
    }

    void TriangleScene::SetBottomLeftPosition(const vec3& position)
    {
        m_BottomLeftPosition = position;
        m_BaseBottomLeftPosition = position / m_TriangleSize;

        CreateTriangle();
    }

    void TriangleScene::SetBottomRightPosition(const vec3& position)
    {
        m_BottomRightPosition = position;
        m_BaseBottomRightPosition = position / m_TriangleSize;

        CreateTriangle();
    }

    void TriangleScene::ResetToDefault()
    {
        m_TriangleSize = m_DefaultTriangleSize;
        m_TopColor = m_DefaultTopColor;
        m_BottomLeftColor = m_DefaultBottomLeftColor;
        m_BottomRightColor = m_DefaultBottomRightColor;

        m_TopPosition = m_DefaultTopPosition;
        m_BottomLeftPosition = m_DefaultBottomLeftPosition;
        m_BottomRightPosition = m_DefaultBottomRightPosition;

        m_BaseTopPosition = m_DefaultTopPosition;
        m_BaseBottomLeftPosition = m_DefaultBottomLeftPosition;
        m_BaseBottomRightPosition = m_DefaultBottomRightPosition;

        m_Camera->SetPosition(m_DefaultCameraPosition);
        m_Camera->SetRotationEuler(m_DefaultCameraRotation);

        CreateTriangle();
    }

    void TriangleScene::RenderSettings()
    {
        constexpr float panelWidth = 340.0f;
        constexpr float panelHeight = 330.0f;
        constexpr float padding = 10.0f;

        const ImGuiIO& io = ImGui::GetIO();
        const float xPos = io.DisplaySize.x - panelWidth - padding;
        const float yPos = io.DisplaySize.y - panelHeight - padding;

        ImGui::SetNextWindowPos(ImVec2(xPos, yPos), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(panelWidth, panelHeight), ImGuiCond_Always);

        ImGui::Begin("Scene Settings", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);

        ImGui::Text("Triangle Properties");
        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        // Triangle Size
        float triangleSize = m_TriangleSize;
        if (ImGui::SliderFloat("Size", &triangleSize, 0.1f, 5.0f, "%.2f"))
        {
            SetTriangleSize(triangleSize);
        }

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        ImGui::Text("Vertex Colors");
        ImGui::Spacing();

        // Top Vertex Color
        float topColor[3] = {m_TopColor.r, m_TopColor.g, m_TopColor.b};
        if (ImGui::ColorEdit3("Top", topColor))
        {
            SetTopColor(Color::RGB(topColor[0], topColor[1], topColor[2]));
        }

        // Bottom Left Vertex Color
        float bottomLeftColor[3] = {m_BottomLeftColor.r, m_BottomLeftColor.g, m_BottomLeftColor.b};
        if (ImGui::ColorEdit3("Bottom Left", bottomLeftColor))
        {
            SetBottomLeftColor(Color::RGB(bottomLeftColor[0], bottomLeftColor[1], bottomLeftColor[2]));
        }

        // Bottom Right Vertex Color
        float bottomRightColor[3] = {m_BottomRightColor.r, m_BottomRightColor.g, m_BottomRightColor.b};
        if (ImGui::ColorEdit3("Bottom Right", bottomRightColor))
        {
            SetBottomRightColor(Color::RGB(bottomRightColor[0], bottomRightColor[1], bottomRightColor[2]));
        }

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        ImGui::Text("Vertex Positions");
        ImGui::Spacing();

        // Top Vertex Position
        vec3 topPos = m_TopPosition;
        if (ImGui::DragFloat3("Top", &topPos.x, 0.01f, -2.0f, 2.0f, "%.2f"))
        {
            SetTopPosition(topPos);
        }

        // Bottom Left Vertex Position
        vec3 bottomLeftPos = m_BottomLeftPosition;
        if (ImGui::DragFloat3("Bottom Left", &bottomLeftPos.x, 0.01f, -2.0f, 2.0f, "%.2f"))
        {
            SetBottomLeftPosition(bottomLeftPos);
        }

        // Bottom Right Vertex Position
        vec3 bottomRightPos = m_BottomRightPosition;
        if (ImGui::DragFloat3("Bottom Right", &bottomRightPos.x, 0.01f, -2.0f, 2.0f, "%.2f"))
        {
            SetBottomRightPosition(bottomRightPos);
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
}
