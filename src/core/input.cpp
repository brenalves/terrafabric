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
}

void Input::updateStates()
{
    for (int i = 0; i < GLFW_KEY_LAST; ++i)
    {
        _previousKeyStates[i] = _currentKeyStates[i];
        _currentKeyStates[i] = (glfwGetKey(glfwGetCurrentContext(), i) == GLFW_PRESS);
    }
}