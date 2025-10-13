#pragma once

#include <glad/glad.h>

#include "buffer.h"
#include "bufferlayout.h"

class VertexArray
{
public:
    VertexArray();
    ~VertexArray();

    void bind() const;

    void addVertexBuffer(const VertexBuffer& vertexBuffer, BufferLayout& layout);

private:
    unsigned int _id;
};