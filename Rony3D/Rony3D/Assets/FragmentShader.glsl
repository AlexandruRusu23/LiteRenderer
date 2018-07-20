//fragment shader
#version 430 core

layout(location = 0) out vec4 out_color;

uniform sampler2D texture_sampler;
in vec2 texcoord;

void main(void)
{
	vec4 color = texture2D(texture_sampler, texcoord);
	out_color = color;
}
