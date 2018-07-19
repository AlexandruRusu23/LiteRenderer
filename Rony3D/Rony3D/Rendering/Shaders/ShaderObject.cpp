#include "ShaderObject.h"

using namespace Rendering::Shaders;

ShaderObject::ShaderObject(const std::string& shaderName, GLuint programId)
	: m_shaderName(shaderName)
	, m_programId(programId)
{

}

ShaderObject::~ShaderObject(void)
{

}

std::string ShaderObject::GetName() const
{
	return m_shaderName;
}

GLuint ShaderObject::GetProgramId() const
{
	return m_programId;
}
