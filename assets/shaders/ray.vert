#version 460 core

layout(location = 0) in vec3 i_Position;

layout (std140, binding = 0) uniform Matrices
{
    mat4 u_Projection;
    mat4 u_View;
    mat4 u_Orthographic;
};

uniform mat4 u_Model;

void main()
{
    gl_Position = u_Projection * u_View * u_Model * vec4(i_Position, 1.0);
}