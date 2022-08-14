//
// Created by Erhan Kurnaz on 02/06/2022.
//

#include <ImGui/imgui.h>
#include "Test.h"

namespace test {
    TestMenu::TestMenu(Test *&currentTestPointer)
        : m_CurrentTest(currentTestPointer) {}

    void TestMenu::OnIMGuiRender() {
        for (auto& test : m_Tests) {
            if (ImGui::Button(test.first.c_str())) {
                m_CurrentTest = test.second();
            }
        }
    }
}