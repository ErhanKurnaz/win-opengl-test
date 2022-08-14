//
// Created by Erhan Kurnaz on 13/08/2022.
//

#pragma once

#include "Input.h"
#include <GLFW/glfw3.h>

class WindowsInput : public Input {
public:
    void SetWindow(GLFWwindow* window) {m_Window = window;}
protected:
    bool IsKeyPressedImpl(int keycode) override;
    bool IsMouseButtonPressedImpl(int button) override;
    std::pair<float, float> GetMousePosImpl() override;
    float GetMouseXImpl() override;
    float GetMouseYImpl() override;

private:
    GLFWwindow* m_Window;
};
