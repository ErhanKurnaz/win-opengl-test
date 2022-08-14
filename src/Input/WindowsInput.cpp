//
// Created by Erhan Kurnaz on 13/08/2022.
//

#include "WindowsInput.h"

Input* Input::s_Instance = new WindowsInput();

bool WindowsInput::IsKeyPressedImpl(int keycode) {
    auto state = glfwGetKey(m_Window, keycode);
    return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool WindowsInput::IsMouseButtonPressedImpl(int button) {
    auto state = glfwGetMouseButton(m_Window, button);
    return state == GLFW_PRESS;
}

std::pair<float, float> WindowsInput::GetMousePosImpl() {
    double xpos, ypos;
    glfwGetCursorPos(m_Window, &xpos, &ypos);
    return { (float) xpos, (float) ypos };
}

float WindowsInput::GetMouseXImpl() {
    return GetMousePosImpl().first;
}

float WindowsInput::GetMouseYImpl() {
    return GetMousePosImpl().second;
}
