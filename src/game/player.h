#pragma once

#include "components/camera.h"
#include "components/transform.h"
#include "core/input.h"
#include "core/timer.h"

class Player
{
public:
    Player();

    void update();

    void onResize(int width, int height);

    inline Transform& getTransform() { return _transform; }
    inline Camera& getCamera() { return _camera; }

private:
    Transform _transform;
    Camera _camera;

    float _speed;
    float _sensitivity;
    float lastX;
    float lastY;
    bool firstMouse = true;
};