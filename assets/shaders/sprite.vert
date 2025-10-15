#version 460 core

layout (location = 0) in vec3 i_Position;
layout (location = 1) in vec2 i_TexCoord;

layout (std140, binding = 0) uniform Matrices
{
    mat4 u_Projection;
    mat4 u_View;
    mat4 u_Orthographic;
};

uniform mat4 u_Model;

out vec2 v_TexCoord;

void main()
{
    gl_Position = u_Orthographic * u_Model * vec4(i_Position, 1.0);
    v_TexCoord = i_TexCoord;
}