//
// Created by Erhan Kurnaz on 02/06/2022.
//

#pragma once

#include "tests/Test/Test.h"
#include "Shader/Shader.h"
#include "VertexArray/VertexArray.h"
#include "IndexBuffer/IndexBuffer.h"
#include "Texture/Texture.h"

namespace test {
    class TestScreensaver : public Test {
    public:
        TestScreensaver();
        ~TestScreensaver();

        void OnUpdate(const AppState& appState) override;

        void OnRender(const Renderer &renderer) override;

        void OnIMGuiRender() override;

    private:
        void Bind();
        void UnBind();

    private:
        struct Player {
            float dx, dy;
        };

        struct Config {
            int bouncesBeforeChange;
        };

        struct State {
            unsigned int bounces;
            unsigned int currColorIndex;
            Player p;
        };

        Shader* m_Shader;
        VertexArray* m_VA;
        VertexBuffer* m_VB;
        Texture* m_Texture;
        IndexBuffer* m_IB;
        glm::vec3 m_Translation;
        Config m_Config{4};
        State m_State{0, 0, {1.0f, 1.0f}};
    };

}
