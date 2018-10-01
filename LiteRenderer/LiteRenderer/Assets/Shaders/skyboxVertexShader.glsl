//vertex shader
#version 430 core

layout (location = 0) in vec3 in_position;

out vec3 texcoords;

uniform mat4 projection_matrix;
uniform mat4 view_matrix;

void main()
{
    texcoords = in_position;
    gl_Position = projection_matrix * view_matrix * vec4(in_position, 1.0);
}
