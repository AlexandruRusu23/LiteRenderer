//fragment shader
#version 430 core

layout(location = 0) out vec4 out_color;

uniform samplerCube skyboxCube;
in vec3 texcoords;

void main(void)
{    
    out_color = texture(skyboxCube, texcoords);
}
