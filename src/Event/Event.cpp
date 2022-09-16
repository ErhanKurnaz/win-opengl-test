//
// Created by Erhan Kurnaz on 14/08/2022.
//

#include "Event.h"

KeyEvent::KeyEvent(int key, bool isPressed, bool isRepeat) : m_key(key), m_isPressed(isPressed), m_isRepeat(isRepeat) {}

void KeyEvent::HandleGLFWEvent(GLFWwindow *window, int key, int scancode, int action, int mods) {
    std::shared_ptr<Event> event = std::make_shared<KeyEvent>(key, action == GLFW_PRESS, action == GLFW_REPEAT);
    Event::s_queue.push(event);
}

int KeyEvent::getKey() const {
    return m_key;
}

bool KeyEvent::isPressed() const {
    return m_isPressed;
}

bool KeyEvent::isRepeat() const {
    return m_isRepeat;
}

std::shared_ptr<Event> Event::PopEvent() {
    auto res = s_queue.front();
    s_queue.pop();
    return res;
}
