#include "input.h"

Input* Input::_instance = nullptr;

Input::Input()
{
    if (_instance != nullptr)
    {
        throw std::runtime_error("Input instance already exists!");
    }

    _instance = this;

    for (int i = 0; i < GLFW_KEY_LAST; ++i)
    {
        _currentKeyStates[i] = false;
        _previousKeyStates[i] = false;
    }

    _mouseX = 400.0f;
    _mouseY = 300.0f;

    _cursorMode = NORMAL;
}

void Input::updateStates()
{
    for (int i = 0; i < GLFW_KEY_LAST; ++i)
    {
        _previousKeyStates[i] = _currentKeyStates[i];
        _currentKeyStates[i] = (glfwGetKey(glfwGetCurrentContext(), i) == GLFW_PRESS);
    }

    double xpos, ypos;
    glfwGetCursorPos(glfwGetCurrentContext(), &xpos, &ypos);
    _mouseX = static_cast<float>(xpos);
    _mouseY = static_cast<float>(ypos);
}

void Input::setCursorMode(CursorMode mode)
{
    _cursorMode = mode;
    glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, static_cast<int>(mode));
}
