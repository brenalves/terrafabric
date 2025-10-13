#include "quad.h"

Quad::Quad()
{
    float vertices[] = {
        // positions        // texture coords
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
         0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
        -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    _mesh = new Mesh();

    _mesh->VBO.setData(sizeof(vertices), vertices);
    _mesh->EBO.setData(sizeof(indices), indices);
    BufferLayout layout;
    layout.push<float>(3); // position
    layout.push<float>(2); // texture coords
    _mesh->VAO.addVertexBuffer(_mesh->VBO, layout);
}

Quad::~Quad()
{
    delete _mesh;
}

void Quad::update()
{
    _transform.updateVectors();

    _transform.rotation.x += 1.0f;
    if(_transform.rotation.x >= 360.0f)
        _transform.rotation.x -= 360.0f;
}
