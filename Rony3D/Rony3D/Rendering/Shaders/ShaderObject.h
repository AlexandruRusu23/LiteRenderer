#ifndef SHADEROBJECT_H
#define SHADEROBJECT_H

#include <string>
#include <glew\glew.h>

#include "Logger.h"

namespace Rendering
{
	namespace Shaders
	{
		class ShaderObject
		{
		public:
			ShaderObject(const std::string& shaderName, GLuint programId);
			virtual ~ShaderObject(void);

			std::string GetName() const;
			GLuint GetProgramId() const;

		protected:
			std::string m_shaderName;
			GLuint		m_programId;
		};
	}
}

#endif // !SHADEROBJECT_H
