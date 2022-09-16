//
// Created by Erhan Kurnaz on 14/08/2022.
//

#pragma once

#include <queue>
#include <memory>
#include "GLFW/glfw3.h"

// TODO: add support for: text input, joystick, gamepad
enum EventType {
    KEY_INPUT,
    MOUSE_MOVE,
    MOUSE_LEAVE,
    MOUSE_ENTERED,
    MOUSE_INPUT,
    MOUSE_SCROLL,
};

class Event {
public:
    virtual EventType GetType() const = 0;
public:
    static std::queue<std::shared_ptr<Event>>* GetQueue() { return &s_queue; }
    static std::shared_ptr<Event> PopEvent();

protected:
    static std::queue<std::shared_ptr<Event>> s_queue;
};

class KeyEvent : public Event {
public:
    KeyEvent(int key, bool isPressed, bool isRepeat);

    [[nodiscard]] EventType GetType() const override { return EventType::KEY_INPUT; }

    int getKey() const;

    bool isPressed() const;

    bool isRepeat() const;

    static void HandleGLFWEvent(GLFWwindow* window, int key, int scancode, int action, int mods);
private:
    int m_key;
    bool m_isPressed;
    bool m_isRepeat;
};
