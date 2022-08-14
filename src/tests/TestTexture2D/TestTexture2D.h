//
// Created by Erhan Kurnaz on 03/06/2022.
//

#pragma once

#include <memory>

#include "tests/Test/Test.h"

namespace test {

    class TestTexture2D : public Test {
    public:
        TestTexture2D();
        ~TestTexture2D();

        void OnUpdate(const AppState &appState) override;

        void OnRender(const Renderer &renderer) override;

        void OnIMGuiRender() override;

    private:
        std::unique_ptr<VertexArray> m_VAO;
        std::unique_ptr<VertexBuffer> m_VertexBuffer;
        std::unique_ptr<IndexBuffer> m_IndexBuffer;
        std::unique_ptr<Shader> m_Shader;
        std::unique_ptr<Texture> m_Texture;

        glm::mat4 m_Proj, m_View;
        glm::vec3 m_TranslationA, m_TranslationB;
    };

} // test
