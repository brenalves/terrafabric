#pragma once

#include <unordered_map>

#include "rendering/shader.h"

class ResourceManager
{
public:
    static Shader* loadShader(const char* name, const char* vertexPath, const char* fragmentPath);
    static Shader* getShader(const char* name);

private:
    static std::unordered_map<const char*, Shader*> _shaders;
};