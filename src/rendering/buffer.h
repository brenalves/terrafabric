#pragma once

#include <glad/glad.h>

class Buffer
{
public:
    Buffer(GLenum type)
        : _type(type)
    {
        glGenBuffers(1, &_id);
    }

    Buffer(GLenum type, unsigned int size, const void* data)
        : _type(type)
    {
        glGenBuffers(1, &_id);
        glBindBuffer(type, _id);
        glBufferData(type, size, data, GL_STATIC_DRAW);
    }
    ~Buffer()
    {
        glDeleteBuffers(1, &_id);
    }

    void bind() const
    {
        glBindBuffer(_type, _id);
    }

    virtual void setData(unsigned int size, const void* data)
    {
        glBindBuffer(_type, _id);
        glBufferData(_type, size, data, GL_STATIC_DRAW);
    }

protected:
    unsigned int _id;

private:
    GLenum _type;
};

class VertexBuffer : public Buffer
{
public:
    VertexBuffer()
        : Buffer(GL_ARRAY_BUFFER)
    {
    }
    VertexBuffer(unsigned int size, const void* data)
        : Buffer(GL_ARRAY_BUFFER, size, data)
    {
    }
};

class IndexBuffer : public Buffer
{
public:
    IndexBuffer()
        : Buffer(GL_ELEMENT_ARRAY_BUFFER)
    {
    }
    IndexBuffer(unsigned int size, const void* data)
        : Buffer(GL_ELEMENT_ARRAY_BUFFER, size, data)
    {
    }

    virtual void setData(unsigned int size, const void* data) override
    {
        _count = size / sizeof(unsigned int);
        Buffer::setData(size, data);
    }

    inline unsigned int getCount() const { return _count; }

private:
    unsigned int _count;
};

class UniformBuffer : public Buffer
{
public:
    UniformBuffer(unsigned int size, unsigned int binding)
        : Buffer(GL_UNIFORM_BUFFER)
    {
        glBindBufferBase(GL_UNIFORM_BUFFER, binding, _id);
        glBufferData(GL_UNIFORM_BUFFER, size, nullptr, GL_STATIC_DRAW);
    }

    void setSubData(unsigned int offset, unsigned int size, const void* data)
    {
        glBindBuffer(GL_UNIFORM_BUFFER, _id);
        glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
    }
};

