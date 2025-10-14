#include "resourcemanager.h"

std::unordered_map<const char*, Shader*> ResourceManager::_shaders;
std::unordered_map<const char*, Texture2D*> ResourceManager::_textures;

void ResourceManager::shutdown()
{
    for(auto& pair : _shaders)
    {
        delete pair.second;
    }
    _shaders.clear();

    for(auto& pair : _textures)
    {
        delete pair.second;
    }
    _textures.clear();
}

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

Texture2D *ResourceManager::loadTexture(const char *name)
{
    if(_textures.find(name) != _textures.end())
    {
        return _textures[name];
    }

    Texture2D* texture = new Texture2D();
    _textures[name] = texture;
    return texture;
}

Texture2D *ResourceManager::getTexture(const char *name)
{
    if (_textures.find(name) != _textures.end())
    {
        return _textures[name];
    }
    return nullptr;
}
