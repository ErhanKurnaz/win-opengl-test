//
// Created by Erhan Kurnaz on 02/06/2022.
//

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <ImGui/imgui.h>

#include "TestScreensaver.h"
#include "VertexBuffer/VertexBufferLayout.h"

#define PRINT_PLAYER(p) "{ dx: " << p.dx << ", dy: " << p.dy << " }"

#define SIZEOF(x) sizeof(x) / sizeof(x[0])

float colors[][4]{
    {1.0f, 0.0f, 0.0f, 1.0f},
    {0.0f, 1.0f, 0.0f, 1.0f},
    {0.0f, 0.0f, 1.0f, 1.0f},
    {0.8f, 0.4f, 0.7f, 1.0f},
};

namespace test {
    #define PLAYER_SIZE 100.0f
    TestScreensaver::TestScreensaver()
    : m_Translation(glm::vec3(0.0f, 0.0f, 0.0f)) {
        float positions[] = {
            0.0f,        0.0f,        0.0f, 0.0f,
            PLAYER_SIZE, 0.0f,        1.0f, 0.0f,
            PLAYER_SIZE, PLAYER_SIZE, 1.0f, 1.0f,
            0.0f,        PLAYER_SIZE, 0.0f, 1.0f,
        };

        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0,
        };

        m_VA = new VertexArray();

        m_VB = new VertexBuffer(positions, 4 * 4 * sizeof(float));

        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        m_VA->AddBuffer(*m_VB, layout);

        m_IB = new IndexBuffer(indices, 6);

        m_Shader = new Shader("res/shaders/Basic.shader");
        m_Shader->Bind();

        m_Texture = new Texture("res/textures/Erpain.png");
        m_Texture->Bind();
        m_Shader->SetUniform1i("u_Texture", 0);
    }

    TestScreensaver::~TestScreensaver() {
        UnBind();

        delete m_VB;
        delete m_VA;
        delete m_IB;
        delete m_Shader;
        delete m_Texture;
    }

    void TestScreensaver::OnUpdate(const AppState& appm_State) {
        m_Translation.x += m_State.p.dx;
        m_Translation.y += m_State.p.dy;

        if (m_Translation.x + PLAYER_SIZE >= (float)appm_State.windowWidth || m_Translation.x <= 0.0f) {
            m_State.p.dx *= -1;
            m_State.bounces++;
        }

        if (m_Translation.y + PLAYER_SIZE >= (float)appm_State.windowHeight || m_Translation.y <= 0.0f) {
            m_State.p.dy *= -1;
            m_State.bounces++;
        }

        if (m_State.bounces >= m_Config.bouncesBeforeChange) {
            m_State.bounces = 0;

            // modulo had some weird behavior and it's way too late for me to care so we doing it like this now bois
            if (m_State.currColorIndex < SIZEOF(colors) - 1) {
                m_State.currColorIndex++;
            } else {
                m_State.currColorIndex = 0;
            }
        }
    }

    void TestScreensaver::OnRender(const Renderer &renderer) {
        auto color = colors[m_State.currColorIndex];
        renderer.Clear(color[0], color[1], color[2], color[3]);
        glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
        glm::mat4 model = glm::translate(glm::mat4(1.0f), m_Translation);

        glm::mat4 mvp = proj * view * model;
        m_Shader->SetUniformMat4f("u_MVP", mvp);

        renderer.Draw(*m_VA, *m_IB, *m_Shader);
    }

    void TestScreensaver::OnIMGuiRender() {
        ImGui::InputInt("Bounces before color change", &m_Config.bouncesBeforeChange);
        ImGui::Text("Bounces: %d", m_State.bounces);
        ImGui::Text("Current color index: %d", m_State.currColorIndex);
    }

    void TestScreensaver::Bind() {
        m_VB->Bind();
        m_VA->Bind();
        m_IB->Bind();
        m_Shader->Bind();
        m_Texture->Bind();
    }

    void TestScreensaver::UnBind() {
        m_VB->Unbind();
        m_VA->Unbind();
        m_IB->Unbind();
        m_Shader->Unbind();
        m_Texture->Unbind();
    }

}