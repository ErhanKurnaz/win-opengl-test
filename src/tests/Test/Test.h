//
// Created by Erhan Kurnaz on 02/06/2022.
//
#pragma once

#include <functional>
#include <vector>
#include <iostream>
#include <ImGui/imgui.h>
#include <glm/glm.hpp>

#include "common/Core.h"

#include "common/Appstate.h"

namespace test {
    class Test {
    public:
        Test() {}
        virtual ~Test() {}

        virtual void OnUpdate(const AppState& appState) {}
        virtual void OnRender(const Renderer& renderer) {}
        virtual void OnIMGuiRender() {}
    };

    class TestMenu : public Test {
    public:
        TestMenu(Test*& currentTestPointer);

        virtual void OnIMGuiRender() override;

        template<typename T>
        void RegisterTest(const std::string& name) {
            std::cout << "Registering test " << name << std::endl;

            m_Tests.push_back(std::make_pair(name, []() { return new T(); }));
        }
    private:
        Test*& m_CurrentTest;
        std::vector<std::pair<std::string, std::function<Test*()>>> m_Tests;
    };
}