#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H

#include <fstream>
#include <iostream>
#include <math.h>
#include <vector>
#include <map>

#include <glew\glew.h>
#include <freeglut\freeglut.h>

namespace Managers
{
	class Shader_Manager
	{
	public:
		Shader_Manager(void);
		~Shader_Manager(void);

		void CreateProgram(const std::string& shaderName, const std::string& VertexShaderFilename, const std::string& FragmentShaderFilename);

		static const GLuint GetShader(const std::string&);

	private:

		std::string ReadShader(const std::string& filename);
		GLuint CreateShader(GLenum shaderType, const std::string& source, const std::string& shaderName);

	private:
		static std::map<std::string, GLuint> ms_programs;
	};
}

#endif
