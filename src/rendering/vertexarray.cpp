#include "vertexarray.h"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &_id);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &_id);
}

void VertexArray::bind() const
{
    glBindVertexArray(_id);
}

void VertexArray::addVertexBuffer(const VertexBuffer &vertexBuffer, BufferLayout &layout)
{
    bind();
    vertexBuffer.bind();

    const auto& elements = layout.getElements();
    unsigned int offset = 0;
    for (unsigned int i = 0; i < elements.size(); i++)
    {
        const auto& element = elements[i];
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const void*)offset);
        offset += element.count * BufferElement::getSizeOfType(element.type);
    }
}
