//vertex shader
#version 430 core

layout (location = 0) in vec4 vertex;
out vec2 TexCoords;

uniform mat4 projection_matrix;

void main()
{
    gl_Position = projection_matrix * vec4(vertex.xy, 0.0, 1.0);
    TexCoords = vertex.zw;
}
