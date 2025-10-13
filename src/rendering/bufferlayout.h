#pragma once

#include <glad/glad.h>
#include <vector>

struct BufferElement
{
    int type;
    int count;
    bool normalized;

    static unsigned int getSizeOfType(int type)
    {
        switch (type)
        {
            case GL_FLOAT: return sizeof(float);
            case GL_UNSIGNED_INT: return sizeof(unsigned int);
            case GL_UNSIGNED_BYTE: return sizeof(unsigned char);
        }
        return 0;
    }
};

class BufferLayout
{
public:
    BufferLayout() : _stride(0) {}
    
    template<typename T>
    void push(int count);

    inline std::vector<BufferElement>& getElements() { return _elements; }
    inline unsigned int getStride() const { return _stride; }

private:
    std::vector<BufferElement> _elements;
    unsigned int _stride;
};

template <typename T>
inline void BufferLayout::push(int count)
{
    static_assert(false, "Unsupported type!");
}

template <>
inline void BufferLayout::push<float>(int count)
{
    _elements.push_back({ GL_FLOAT, count, GL_FALSE });
    _stride += sizeof(float) * count;
}
