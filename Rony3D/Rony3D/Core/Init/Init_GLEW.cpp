#include "Init_GLEW.h"
using namespace Core;
using namespace Core::Init;

void Init_GLEW::Init()
{
	glewExperimental = true;
	if (glewInit() == GLEW_OK)
	{
		std::cout << "GLEW: Initialize" << std::endl;
	}

	std::cout << "OpenGL version supported by this platform: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL version supported by this platform: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

}
