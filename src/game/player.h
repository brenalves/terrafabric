#pragma once

#include "components/camera.h"
#include "components/transform.h"

class Player
{
public:
    Player();

    void update();

    inline Transform& getTransform() { return _transform; }
    inline Camera& getCamera() { return _camera; }

private:
    Transform _transform;
    Camera _camera;

    float _speed;
};