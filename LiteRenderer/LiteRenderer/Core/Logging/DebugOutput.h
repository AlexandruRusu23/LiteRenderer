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
				DebugOutput() = delete;
				~DebugOutput() = delete;
				DebugOutput(DebugOutput& debugOutput) = delete;
				DebugOutput& operator=(const DebugOutput& debugOutput) = delete;

				static void CALLBACK RegisterDebugError(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *msg, const void *data)
				{
					switch (severity)
					{
					case GL_DEBUG_SEVERITY_HIGH:
						if (!(Logger::GetFlags() & Logger::LOG_HIGH_ERRORS))
							return;
						break;
					case GL_DEBUG_SEVERITY_MEDIUM:
						if (!(Logger::GetFlags() & Logger::LOG_MEDIUM_ERRORS))
							return;
						break;
					case GL_DEBUG_SEVERITY_LOW:
						if (!(Logger::GetFlags() & Logger::LOG_LOW_ERRORS))
							return;
						break;
					case GL_DEBUG_SEVERITY_NOTIFICATION:
						if (!(Logger::GetFlags() & Logger::LOG_NOTIFICATIONS))
							return;
						break;
					default:
						assert(false);
						return;
					}

					Logger::Log("**********Debug Output**************");
					Logger::Log("Source: %s", GetStringForSource(source).c_str());
					Logger::Log("Type: %s", GetStringForType(type).c_str());
					Logger::Log("Severity: %s", GetStringForSeverity(severity).c_str());
					Logger::Log("Debug Call: %s", msg);
					Logger::Log("************************************");
					Logger::Log("");
				}

			private:
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

