#pragma once

#include "rendering/buffer.h"
#include "rendering/vertexarray.h"

struct Mesh
{
    VertexArray VAO;
    VertexBuffer VBO;
    IndexBuffer EBO;
};