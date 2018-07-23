#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H

#include <map>

#include <glew/glew.h>

#include "Rendering/Shaders/ShaderObject.h"
#include "Rendering/Shaders/DrawingShader.h"

namespace Managers
{
	class ShaderManager
	{
	public:
		ShaderManager(void);
		~ShaderManager(void);

		Rendering::Shaders::ShaderObject* GetShader(const std::string& shaderName);

		void CreateProgram(const std::string& shaderName, 
			const std::string& vertexShaderFilename, 
			const std::string& fragmentShaderFilename,
			const std::string& geometryShaderFilename = "");

	private:
		std::string ReadShader(const std::string& filename);
		GLuint CreateShader(GLenum shaderType, const std::string& source, const std::string& shaderName);

		std::map<std::string, Rendering::Shaders::ShaderObject*> m_programs;
	};
}

#endif
