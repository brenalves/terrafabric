#include "timer.h"

Timer* Timer::_instance = nullptr;

Timer::Timer()
{
    if (_instance)
    {
        throw std::runtime_error("Timer instance already exists!");
    }

    _instance = this;

    _deltaTime = 0.0f;
    _lastFrameTime = 0.0f;
}

void Timer::update()
{
    float currentTime = static_cast<float>(glfwGetTime());
    _deltaTime = currentTime - _lastFrameTime;
    _lastFrameTime = currentTime;
}
