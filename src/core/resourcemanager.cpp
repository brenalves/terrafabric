#include "resourcemanager.h"

std::unordered_map<std::string, Shader*> ResourceManager::_shaders;
std::unordered_map<std::string, Texture2D*> ResourceManager::_textures;
std::unordered_map<std::string, Mesh*> ResourceManager::_meshes;

void ResourceManager::shutdown()
{
    for(auto& pair : _shaders)
    {
        if(pair.second)
            delete pair.second;
    }
    _shaders.clear();

    for(auto& pair : _textures)
    {
        if(pair.second)
            delete pair.second;
    }
    _textures.clear();

    for(auto& pair : _meshes)
    {
        if(pair.second)
            delete pair.second;
    }
    _meshes.clear();
}

Shader *ResourceManager::loadShader(const std::string &name, const std::string &vertexPath, const std::string &fragmentPath)
{
    if(_shaders.find(name) != _shaders.end())
    {
        return _shaders[name];
    }

    Shader* shader = new Shader(vertexPath.c_str(), fragmentPath.c_str());
    _shaders[name] = shader;
    return shader;
}

Shader *ResourceManager::getShader(const std::string &name)
{
    if (_shaders.find(name) != _shaders.end())
    {
        return _shaders[name];
    }
    return nullptr;
}

Texture2D *ResourceManager::loadTexture(const std::string &name)
{
    if(_textures.find(name) != _textures.end())
    {
        return _textures[name];
    }

    Texture2D* texture = new Texture2D();
    _textures[name] = texture;
    return texture;
}

Texture2D *ResourceManager::getTexture(const std::string &name)
{
    if (_textures.find(name) != _textures.end())
    {
        return _textures[name];
    }
    return nullptr;
}

Mesh *ResourceManager::loadMesh(const std::string &name)
{
    if(_meshes.find(name) != _meshes.end())
    {
        return _meshes[name];
    }

    Mesh* mesh = new Mesh();
    _meshes[name] = mesh;
    return mesh;
}

Mesh *ResourceManager::getMesh(const std::string &name)
{
    if( _meshes.find(name) != _meshes.end())
    {
        return _meshes[name];
    }
    return nullptr;
}
