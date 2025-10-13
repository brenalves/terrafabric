#pragma once

#include "components/transform.h"
#include "components/mesh.h"

class Quad
{
public:
    Quad();
    ~Quad();

    void update();

    inline Transform& getTransform() { return _transform; }
    inline Mesh* getMesh() { return _mesh; }

private:
    Transform _transform;
    Mesh* _mesh;
};