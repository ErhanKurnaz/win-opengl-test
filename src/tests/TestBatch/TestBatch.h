//
// Created by Erhan Kurnaz on 03/06/2022.
//

#pragma once

#include "tests/Test/Test.h"
#include "Camera/OrthographicCamera.h"

namespace test {

    class TestBatch : public Test {
    public:
        TestBatch();
        ~TestBatch();

        void OnUpdate(const AppState &appState) override;

        void OnRender(const Renderer &renderer) override;

        void OnIMGuiRender() override;

        void OnEvent(const Event &event) override;

    private:
        std::unique_ptr<VertexArray> m_VAO;
        std::unique_ptr<VertexBuffer> m_VertexBuffer;
        std::unique_ptr<IndexBuffer> m_IndexBuffer;
        std::unique_ptr<Shader> m_Shader;
        std::unique_ptr<Texture> m_Texture;

        OrthographicCamera m_Camera;
    };

}
