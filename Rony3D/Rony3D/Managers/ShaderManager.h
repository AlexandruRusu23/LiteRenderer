#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H

#include <map>

#include <glew\glew.h>
#include <freeglut\freeglut.h>

namespace Managers
{
	class ShaderManager
	{
	public:
		ShaderManager(void);
		~ShaderManager(void);

		static const GLuint GetShader(const std::string& shaderName);

		void CreateProgram(const std::string& shaderName, const std::string& VertexShaderFilename, const std::string& FragmentShaderFilename);

	private:
		std::string ReadShader(const std::string& filename);
		GLuint CreateShader(GLenum shaderType, const std::string& source, const std::string& shaderName);

		static std::map<std::string, GLuint> m_programs;
	};
}

#endif
