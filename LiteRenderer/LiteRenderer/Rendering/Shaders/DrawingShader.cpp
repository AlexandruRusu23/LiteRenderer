#include "DrawingShader.h"

using namespace LiteRenderer;
using namespace Rendering;
using namespace Shaders;

DrawingShader::DrawingShader(const std::string& shaderName,
	GLuint programId,
	GLuint vertexShaderId,
	GLuint fragmentShaderId,
	GLuint geometryShaderId /* = 0 */)
	: ShaderObject(shaderName, programId)
	, m_vertexShaderId(vertexShaderId)
	, m_fragmentShaderId(fragmentShaderId)
	, m_geometryShaderId(geometryShaderId)
{

}

DrawingShader::~DrawingShader()
{
	glDetachShader(m_programId, m_vertexShaderId);
	glDetachShader(m_programId, m_fragmentShaderId);
	glDetachShader(m_programId, m_geometryShaderId);

	glDeleteShader(m_vertexShaderId);
	glDeleteShader(m_fragmentShaderId);
	glDeleteShader(m_geometryShaderId);

	glDeleteProgram(m_programId);
}

GLuint DrawingShader::GetVertexShader() const
{
	return m_vertexShaderId;
}

GLuint DrawingShader::GetFragmentShader() const
{
	return m_fragmentShaderId;
}

GLuint DrawingShader::GetGeometryShader() const
{
	return m_geometryShaderId;
}

void DrawingShader::SetVertexShaderFilename(const std::string& filename)
{
	m_vertexShaderFilename = filename;
}

void DrawingShader::SetFragmentShaderFilename(const std::string& filename)
{
	m_fragmentShaderFilename = filename;
}

void DrawingShader::SetGeometryShaderFilename(const std::string& filename)
{
	m_geometryShaderFilename = filename;
}

