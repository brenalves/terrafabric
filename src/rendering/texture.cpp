#include "texture.h"

Texture2D::Texture2D()
{
    glGenTextures(1, &_id);

    // Set default texture parameters
    setFiltering(GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST);
    setWrapMode(GL_REPEAT, GL_REPEAT);
}

Texture2D::~Texture2D()
{
    glDeleteTextures(1, &_id);
}

void Texture2D::loadFromFile(const char *path)
{
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path, &_width, &_height, &_channels, 4);
    if(!data)
    {
        const char* msg = stbi_failure_reason();
        throw std::runtime_error(msg);
    }

    glBindTexture(GL_TEXTURE_2D, _id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
}

void Texture2D::bind(unsigned int slot) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, _id);
}

void Texture2D::setFiltering(GLenum minFilter, GLenum magFilter)
{
    glBindTexture(GL_TEXTURE_2D, _id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
}

void Texture2D::setWrapMode(GLenum wrapS, GLenum wrapT)
{
    glBindTexture(GL_TEXTURE_2D, _id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
}
