//fragment shader
#version 430 core

layout(location = 0) out vec4 out_color;

//in vec4 color;
uniform sampler2D texture1;
in vec2 texcoord;

void main(void)
{
	vec4 color = texture(texture1, texcoord);
	out_color = color;
}