#ifndef MANAGERS_SHADERMANAGER_H
#define MANAGERS_SHADERMANAGER_H

#include <map>

#include <glew/glew.h>

#include "Rendering/Shaders/ShaderObject.h"
#include "Rendering/Shaders/DrawingShader.h"

namespace LiteRenderer
{
	namespace Managers
	{
		class ShaderManager
		{
		public:
			ShaderManager(void);
			~ShaderManager(void);

			Rendering::Shaders::ShaderObject& GetShader(const std::string& shaderName);

			void CreateProgram(const std::string& shaderName,
				const std::string& vertexShaderFilename,
				const std::string& fragmentShaderFilename,
				const std::string& geometryShaderFilename = "");

		private:
			std::string ReadShader(const std::string& filename);
			GLuint CreateShader(GLenum shaderType, const std::string& source, const std::string& shaderName);

			std::map<std::string, std::unique_ptr<Rendering::Shaders::ShaderObject>> m_programs;
		};
	}
}

#endif // !MANAGERS_SHADERMANAGER_H

