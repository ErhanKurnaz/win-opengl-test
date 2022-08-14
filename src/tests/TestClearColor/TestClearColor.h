//
// Created by Erhan Kurnaz on 02/06/2022.
//
#pragma once

#include "tests/Test/Test.h"

namespace test {
    class TestClearColor : public Test {
    public:
        TestClearColor();
        ~TestClearColor();

        void OnUpdate(const AppState& appState) override;
        void OnRender(const Renderer& renderer) override;
        void OnIMGuiRender() override;
    private:
        float m_ClearColor[4];
    };
}
