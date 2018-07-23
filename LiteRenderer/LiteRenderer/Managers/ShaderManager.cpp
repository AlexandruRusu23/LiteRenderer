#include "ShaderManager.h"

#include <iostream>
#include <fstream>
#include <vector>

#include "Logger.h"

using namespace Managers;
using namespace Rendering::Shaders;

ShaderManager::ShaderManager(void) {}

ShaderManager::~ShaderManager(void)
{
	std::map<std::string, ShaderObject*>::iterator program;
	for (program = m_programs.begin(); program != m_programs.end(); program++)
	{
		ShaderObject* shader = program->second;
		delete shader;
	}
	m_programs.clear();
}

ShaderObject* ShaderManager::GetShader(const std::string& shaderName)
{
	if (m_programs.find(shaderName) != m_programs.end())
		return m_programs.at(shaderName);
	return nullptr;
}

void ShaderManager::CreateProgram(const std::string& shaderName,
	const std::string& vertexShaderFilename,
	const std::string& fragmentShaderFilename,
	const std::string& geometryShaderFilename /* = "" */)
{
	if (m_programs.find(shaderName) != m_programs.end())
		return;

	std::string vertexShaderCode = ReadShader(vertexShaderFilename);
	std::string fragmentShaderCode = ReadShader(fragmentShaderFilename);
	std::string geometryShaderCode = "";
	GLuint vertexShader = CreateShader(GL_VERTEX_SHADER, vertexShaderCode, std::string("vertex_shader").c_str());
	GLuint fragmentShader = CreateShader(GL_FRAGMENT_SHADER, fragmentShaderCode, std::string("fragment_shader").c_str());
	GLuint geometryShader = 0;

	if (geometryShaderFilename != "")
	{
		geometryShaderCode = ReadShader(geometryShaderFilename);
		geometryShader = CreateShader(GL_GEOMETRY_SHADER, geometryShaderCode, std::string("fragment_shader").c_str());
	}

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
		Logger::Log("Shader Loader : LINK ERROR");
		Logger::Log(&programLog[0]);
		return;
	}

	DrawingShader* shader = new DrawingShader(shaderName, program, vertexShader, fragmentShader, geometryShader);
	shader->SetVertexShaderFilename(vertexShaderFilename);
	shader->SetFragmentShaderFilename(vertexShaderFilename);
	shader->SetGeometryShaderFilename(geometryShaderFilename);

	m_programs[shaderName] = shader;
}

std::string ShaderManager::ReadShader(const std::string& filename)
{
	std::string shaderCode;
	std::ifstream file(filename.c_str(), std::ios::in);

	if (!file)
	{
		Logger::Log("Could not open the file %s.", filename.c_str());
		return 0;
	}

	if (!file.good())
	{
		Logger::Log("Can't read file %s.", filename.c_str());
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
		Logger::Log("Error compiling shader: %s", shaderName.c_str());
		Logger::Log(&shaderLog[0]);
		return 0;
	}
	return shader;
}
