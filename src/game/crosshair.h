#pragma once

#include "core/resourcemanager.h"

#include "components/transform.h"

class Crosshair
{
public:
    Crosshair();

    void update();

    inline Transform& getTransform() { return _transform; }
    inline Texture2D* getTexture() { return _texture; }

private:
    Transform _transform;
    Texture2D* _texture;
};