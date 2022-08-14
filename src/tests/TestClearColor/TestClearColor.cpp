//
// Created by Erhan Kurnaz on 02/06/2022.
//
#include <ImGui/imgui.h>
#include "TestClearColor.h"

namespace test {

    TestClearColor::TestClearColor()
        : m_ClearColor{0.2f, 0.3f, 0.8f, 1.0f} {

    }

    TestClearColor::~TestClearColor() {

    }

    void TestClearColor::OnUpdate(const AppState& appState) {
        Test::OnUpdate(appState);
    }

    void TestClearColor::OnRender(const Renderer &renderer) {
        renderer.Clear(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]);
    }

    void TestClearColor::OnIMGuiRender() {
        ImGui::ColorEdit4("Clear Color", m_ClearColor);
    }
}
