#include "ShaderManager.h"

#include <iostream>
#include <fstream>
#include <vector>

using namespace Managers;

// static std::map from ShaderManager class;
std::map <std::string, GLuint> ShaderManager::m_programs;

ShaderManager::ShaderManager(void) {}

ShaderManager::~ShaderManager(void)
{
	std::map<std::string, GLuint>::iterator program;
	for (program = m_programs.begin(); program != m_programs.end(); program++)
	{
		GLuint pr = program->second;
		glDeleteProgram(pr);
	}
	m_programs.clear();
}

std::string ShaderManager::ReadShader(const std::string& filename)
{
	std::string shaderCode;
	std::ifstream file(filename.c_str(), std::ios::in);

	if (!file)
	{
		std::cout << "Could not open the file." << std::endl;
		return 0;
	}

	if (!file.good())
	{
		std::cout << "Can't read file" << filename.c_str() << std::endl;
		std::terminate();
		return 0;
	}

	file.seekg(0, std::ios::end);
	shaderCode.resize((unsigned int)file.tellg());
	file.seekg(0, std::ios::beg);
	file.read(&shaderCode[0], shaderCode.size());
	file.close();

	return shaderCode;
}

GLuint ShaderManager::CreateShader(GLenum shaderType, const std::string& source, const std::string& shaderName)
{
	GLuint shader = glCreateShader(shaderType);
	const char *shaderCodePtr = source.c_str();
	const int shaderCodeSize = static_cast<int>(source.size());

	int compileResult = 0;
	glShaderSource(shader, 1, &shaderCodePtr, &shaderCodeSize);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);

	if (compileResult == GL_FALSE)
	{
		int infoLogLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
		std::vector<char> shaderLog(infoLogLength);
		glGetShaderInfoLog(shader, infoLogLength, NULL, &shaderLog[0]);
		std::cout << "ERROR compiling shader: " << shaderName.c_str() << std::endl << &shaderLog[0] << std::endl;
		return 0;
	}
	return shader;
}

void ShaderManager::CreateProgram(const std::string& shaderName, const std::string& VertexShaderFilename, const std::string& FragmentShaderFilename)
{
	std::string vertexShaderCode = ReadShader(VertexShaderFilename);
	std::string fragmentShaderCode = ReadShader(FragmentShaderFilename);
	GLuint vertexShader = CreateShader(GL_VERTEX_SHADER, vertexShaderCode, (std::string("vertex shader")).c_str());
	GLuint fragmentShader = CreateShader(GL_FRAGMENT_SHADER, fragmentShaderCode, (std::string("fragment shader")).c_str());

	GLuint program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	int linkResult = 0;
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &linkResult);

	if (linkResult == GL_FALSE)
	{
		int infoLogLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
		std::vector<char> programLog(infoLogLength);
		glGetProgramInfoLog(program, infoLogLength, NULL, &programLog[0]);
		std::cout << "Shader Loader : LINK ERROR" << std::endl << &programLog[0] << std::endl;
		return;
	}
	// check if shaderName is already in std::map
	if (m_programs.find(shaderName) != m_programs.end())
		return;
	m_programs[shaderName] = program;
}

const GLuint ShaderManager::GetShader(const std::string& shaderName)
{
	if (m_programs.find(shaderName) != m_programs.end())
		return m_programs.at(shaderName);
	return -1;
}
