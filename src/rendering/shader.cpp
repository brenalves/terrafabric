#include "shader.h"

Shader::Shader(const char *vertexPath, const char *fragmentPath)
{
    unsigned int vertexShader = createAndCompileShader(vertexPath, GL_VERTEX_SHADER);
    unsigned int fragmentShader = createAndCompileShader(fragmentPath, GL_FRAGMENT_SHADER);

    _id = glCreateProgram();
    glAttachShader(_id, vertexShader);
    glAttachShader(_id, fragmentShader);
    glLinkProgram(_id);

    int success;
    glGetProgramiv(_id, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(_id, 512, nullptr, infoLog);
        throw std::runtime_error(std::string("Shader program linking failed: ") + infoLog);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
    glDeleteProgram(_id);
}

void Shader::bind() const
{
    glUseProgram(_id);
}

unsigned int Shader::createAndCompileShader(const char *source, GLenum shaderType)
{
    std::fstream file(source);
    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open shader file");
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string sourceStr = buffer.str();
    const char* sourceCStr = sourceStr.c_str();

    unsigned int shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &sourceCStr, nullptr);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        throw std::runtime_error(std::string("Shader compilation failed: ") + infoLog);
    }

    return shader;
}

int Shader::getUniformLocation(const char *name)
{
    if(_uniformLocationCache.find(name) == _uniformLocationCache.end())
    {
        int location = glGetUniformLocation(_id, name);
        if(location == -1)
        {
            throw std::runtime_error(std::string("Uniform not found: ") + name);
        }
        _uniformLocationCache[name] = location;
    }

    return _uniformLocationCache[name];
}
