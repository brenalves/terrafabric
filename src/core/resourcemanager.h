#pragma once

#include <unordered_map>

#include "rendering/shader.h"
#include "rendering/texture.h"

class ResourceManager
{
public:
    static void shutdown();

    static Shader* loadShader(const char* name, const char* vertexPath, const char* fragmentPath);
    static Shader* getShader(const char* name);

    static Texture2D* loadTexture(const char* name);
    static Texture2D* getTexture(const char* name);

private:
    static std::unordered_map<const char*, Shader*> _shaders;
    static std::unordered_map<const char*, Texture2D*> _textures;
};