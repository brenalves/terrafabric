#pragma once

#include <GLFW/glfw3.h>
#include <stdexcept>

class Timer
{
public:
    Timer();

    void update();

    inline float getDeltaTime() const { return _deltaTime; }

    static Timer* getInstance() { return _instance; }

private:
    float _deltaTime;
    float _lastFrameTime;

    static Timer* _instance;
};