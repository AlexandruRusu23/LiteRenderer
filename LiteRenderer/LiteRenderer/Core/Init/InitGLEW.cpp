#include "InitGLEW.h"
#include "Logger.h"

using namespace LiteRenderer;
using namespace Core;
using namespace Init;

InitGLEW::InitGLEW(void)
{

}

InitGLEW::~InitGLEW(void)
{

}

void InitGLEW::Init()
{
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		Logger::Log("glewInit() error");
		return;
	}

	Logger::Log("GLEW: Initialized");
	Logger::Log("OpenGL version supported by this platform: %s", glGetString(GL_VERSION));
	Logger::Log("GLSL version supported by this platform: %s", glGetString(GL_SHADING_LANGUAGE_VERSION));
}

