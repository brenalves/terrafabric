#pragma once

#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <unordered_map>

class Shader
{
public:
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();

    void bind() const;

    inline void setUniformMatrix4fv(const char* name, const float* value)
    {
        glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, value);
    }

private:
    unsigned int createAndCompileShader(const char* source, GLenum shaderType);
    int getUniformLocation(const char* name);

private:
    unsigned int _id;
    std::unordered_map<const char*, int> _uniformLocationCache;
};