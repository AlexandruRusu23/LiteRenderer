#include "InitGLEW.h"

using namespace Core;
using namespace Core::Init;

InitGLEW::InitGLEW(void)
{

}

InitGLEW::~InitGLEW(void)
{

}

void InitGLEW::Init()
{
	glewExperimental = true;

	if (glewInit() == GLEW_OK)
	{
		std::cout << "GLEW: Initialized" << std::endl;
	}

	std::cout << "OpenGL version supported by this platform: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL version supported by this platform: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
}
