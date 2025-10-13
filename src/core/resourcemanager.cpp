#include "resourcemanager.h"

std::unordered_map<const char*, Shader*> ResourceManager::_shaders;

Shader *ResourceManager::loadShader(const char *name, const char *vertexPath, const char *fragmentPath)
{
    if(_shaders.find(name) != _shaders.end())
    {
        return _shaders[name];
    }

    Shader* shader = new Shader(vertexPath, fragmentPath);
    _shaders[name] = shader;
    return shader;
}

Shader *ResourceManager::getShader(const char *name)
{
    if (_shaders.find(name) != _shaders.end())
    {
        return _shaders[name];
    }
    return nullptr;
}
