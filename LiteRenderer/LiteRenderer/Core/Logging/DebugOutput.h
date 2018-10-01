#ifndef LOGGING_DEBUGOUTPUT_H
#define LOGGING_DEBUGOUTPUT_H

#include <string>
#include <iostream>
#include <glew/glew.h>
#include <freeglut/freeglut.h>
#include <assert.h>

#include "Logger.h"

namespace LiteRenderer
{
	namespace Core
	{
		namespace Logging
		{
			class DebugOutput
			{
			public:

				static void CALLBACK RegisterDebugError(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *msg, const void *data)
				{
					Logger::Log("\n**********Debug Output**************");
					Logger::Log("source: %s", GetStringForSource(source).c_str());
					Logger::Log("type: %s", GetStringForType(type).c_str());
					Logger::Log("severity: %s", GetStringForSeverity(severity).c_str());
					Logger::Log("debug call: %s", msg);
					Logger::Log("\n************************");
				}

			private:
				DebugOutput(void) {};
				~DebugOutput(void) {};

				static std::string GetStringForType(GLenum type)
				{
					switch (type)
					{
					case GL_DEBUG_TYPE_ERROR:
						return"Error";
					case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
						return "Deprecated behavior";
					case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
						return "Undefined behavior";
					case GL_DEBUG_TYPE_PORTABILITY:
						return "Portability issue";
					case GL_DEBUG_TYPE_PERFORMANCE:
						return "Performance issue";
					case GL_DEBUG_TYPE_MARKER:
						return "Stream annotation";
					case GL_DEBUG_TYPE_OTHER_ARB:
						return "Other";
					default:
						assert(false);
						return "";
					}
				}

				static std::string GetStringForSource(GLenum source)
				{
					switch (source)
					{
					case GL_DEBUG_SOURCE_API:
						return "API";
					case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
						return "Window system";
					case GL_DEBUG_SOURCE_SHADER_COMPILER:
						return "Shader compiler";
					case GL_DEBUG_SOURCE_THIRD_PARTY:
						return "Third party";
					case GL_DEBUG_SOURCE_APPLICATION:
						return "Application";
					case GL_DEBUG_SOURCE_OTHER:
						return "Other";
					default:
						assert(false);
						return "";
					}
				}

				static std::string GetStringForSeverity(GLenum severity)
				{
					switch (severity)
					{
					case GL_DEBUG_SEVERITY_HIGH:
						return "High";
					case GL_DEBUG_SEVERITY_MEDIUM:
						return "Medium";
					case GL_DEBUG_SEVERITY_LOW:
						return "Low";
					case GL_DEBUG_SEVERITY_NOTIFICATION:
						return "Notification";
					default:
						assert(false);
						return("");
					}
				}

			};
		}
	}
}

#endif // !LOGGING_DEBUGOUTPUT_H

