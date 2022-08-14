//
// Created by Erhan Kurnaz on 03/06/2022.
//

#include <array>

#include "TestBatch.h"
#include <glm/gtc/matrix_transform.hpp>

#define ARR_FLOAT_SIZE(type, field) (sizeof(((type*)0)->field) / sizeof(float))

#define HOR_VAL 10.0f
#define VERT_VAL 10.0f

namespace test {
    struct Vertex {
        glm::vec3 Position;
        glm::vec4 Color;
        glm::vec2 TexCoords;
        float TexID;
    };

    TestBatch::TestBatch()
        : m_Camera(-HOR_VAL, HOR_VAL, -VERT_VAL, VERT_VAL) {

        const unsigned int maxQuadCount = 1000;
        const unsigned int maxVertexCount = maxQuadCount * 4;
        const unsigned int maxIndexCount = maxQuadCount * 6;

        /*
        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0,
            4, 5, 6,
            6, 7, 4,
        };
         */
        unsigned int indices[maxIndexCount];
        unsigned int offset = 0;
        for (unsigned int i = 0; i < maxIndexCount; i += 6) {
            indices[i + 0] = 0 + offset;
            indices[i + 1] = 1 + offset;
            indices[i + 2] = 2 + offset;

            indices[i + 3] = 2 + offset;
            indices[i + 4] = 3 + offset;
            indices[i + 5] = 0 + offset;

            offset += 4;
        }

        m_VAO = std::make_unique<VertexArray>();
        m_VertexBuffer = std::make_unique<VertexBuffer>(nullptr, maxVertexCount * sizeof(Vertex));

        VertexBufferLayout layout;
        // position
        layout.Push<float>(ARR_FLOAT_SIZE(Vertex, Position));
        // color
        layout.Push<float>(ARR_FLOAT_SIZE(Vertex, Color));
        // texture coord
        layout.Push<float>(ARR_FLOAT_SIZE(Vertex, TexCoords));
        // texture id
        layout.Push<float>(ARR_FLOAT_SIZE(Vertex, TexID));
        m_VAO->AddBuffer(*m_VertexBuffer, layout);

        m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 12);

        m_Shader = std::make_unique<Shader>("res/shaders/Triangle.shader");
        m_Shader->Bind();
        int samplers[2] = {0, 1};
        m_Shader->SetUniform1iv("u_Textures", sizeof(samplers), samplers);
        m_Texture = std::make_unique<Texture>("res/textures/Erpain.png");
        m_Texture->Bind(1);
    }

    TestBatch::~TestBatch() {

    }

    static Vertex* CreateQuad(Vertex* target, float x, float y, float textureID) {
        float size = 1.0f;

        target->Position = {x, y, 0.0f};
        target->Color = {0.18f, 0.6f, 0.96f, 1.0f};
        target->TexCoords = {0.0f, 0.0f};
        target->TexID = textureID;
        target++;

        target->Position = {x + size, y, 0.0f};
        target->Color = {0.18f, 0.6f, 0.96f, 1.0f};
        target->TexCoords = {1.0f, 0.0f};
        target->TexID = textureID;
        target++;

        target->Position = {x + size, y + size, 0.0f};
        target->Color = {0.18f, 0.6f, 0.96f, 1.0f};
        target->TexCoords = {1.0f, 1.0f};
        target->TexID = textureID;
        target++;

        target->Position = {x,  y + size, 0.0f};
        target->Color = {0.18f, 0.6f, 0.96f, 1.0f};
        target->TexCoords = {0.0f, 1.0f};
        target->TexID = textureID;
        target++;

        return target;
    }

    void TestBatch::OnUpdate(const AppState &appState) {
        /*
        float vertices[] = {
            -1.5f, -0.5f, 0.0f, 0.18f, 0.6f, 0.96f, 1.0f, 0.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, 0.0f, 0.18f, 0.6f, 0.96f, 1.0f, 1.0f, 0.0f, 0.0f,
            -0.5f,  0.5f, 0.0f, 0.18f, 0.6f, 0.96f, 1.0f, 1.0f, 1.0f, 0.0f,
            -1.5f,  0.5f, 0.0f, 0.18f, 0.6f, 0.96f, 1.0f, 0.0f, 1.0f, 0.0f,

            0.5f, -0.5f, 0.0f, 1.0f, 0.93f, 0.24f, 1.0f, 0.0f, 0.0f, 1.0f,
            1.5f, -0.5f, 0.0f, 1.0f, 0.93f, 0.24f, 1.0f, 1.0f, 0.0f, 1.0f,
            1.5f,  0.5f, 0.0f, 1.0f, 0.93f, 0.24f, 1.0f, 1.0f, 1.0f, 1.0f,
            0.5f,  0.5f, 0.0f, 1.0f, 0.93f, 0.24f, 1.0f, 0.0f, 1.0f, 1.0f,
        };
         */

        #define CAMERA_STEP 0.01f
        if (Input::IsKeyPressed(KEY_A)) {
            auto& pos = m_Camera.GetPosition();
            m_Camera.SetPosition({ pos.x - CAMERA_STEP, pos.y, pos.z });
        }
        if (Input::IsKeyPressed(KEY_D)) {
            auto& pos = m_Camera.GetPosition();
            m_Camera.SetPosition({ pos.x + CAMERA_STEP, pos.y, pos.z });
        }
        if (Input::IsKeyPressed(KEY_S)) {
            auto& pos = m_Camera.GetPosition();
            m_Camera.SetPosition({ pos.x, pos.y - CAMERA_STEP, pos.z });
        }
        if (Input::IsKeyPressed(KEY_W)) {
            auto& pos = m_Camera.GetPosition();
            m_Camera.SetPosition({ pos.x, pos.y + CAMERA_STEP, pos.z });
        }
        if (Input::IsKeyPressed(KEY_LEFT_SHIFT)) {
            auto& pos = m_Camera.GetPosition();
            m_Camera.SetPosition({ pos.x, pos.y, pos.z + CAMERA_STEP });
        }

        std::array<Vertex, 1000> vertices;
        Vertex* buffer = vertices.data();

        for (int y = 0; y < 5; y++) {
            for (int x = 0; x < 5; x++) {
                buffer = CreateQuad(buffer, (float)x, (float)y, (float)((x + y) % 2));
            }
        }

        buffer = CreateQuad(buffer, -1.5, -0.5f, 0.0f);

        m_VertexBuffer->SetSubData(vertices.data(), vertices.size(), 0);
        // m_VertexBuffer->SetSubData(vertices, sizeof(vertices), 0);
    }

    void TestBatch::OnRender(const Renderer &renderer) {
        renderer.Clear(0.1f, 0.1f, 0.1f, 1.0f);

        m_Shader->SetUniformMat4f("u_ViewProjection", m_Camera.GetViewProjectionMatrix());
//        m_Shader->SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);

        renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
    }

    void TestBatch::OnIMGuiRender() {
    }
} // test