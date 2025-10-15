#pragma once

#include "rendering/buffer.h"
#include "rendering/vertexarray.h"

struct Mesh
{
    VertexArray* VAO;
    VertexBuffer* VBO;
    IndexBuffer* EBO;

    Mesh()
        : VAO(new VertexArray()), VBO(new VertexBuffer()), EBO(new IndexBuffer())
    {
    }

    ~Mesh()
    {
        delete VAO;
        delete VBO;
        delete EBO;
    }
};