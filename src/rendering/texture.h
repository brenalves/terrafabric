#pragma once

#include <glad/glad.h>
#include <stb_image.h>
#include <stdexcept>

class Texture2D
{
public:
    Texture2D();
    ~Texture2D();

    void loadFromFile(const char* path);

    void bind(unsigned int slot = 0) const;

    void setFiltering(GLenum minFilter, GLenum magFilter);
    void setWrapMode(GLenum wrapS, GLenum wrapT);

private:
    unsigned int _id;
    int _width;
    int _height;
    int _channels;
};