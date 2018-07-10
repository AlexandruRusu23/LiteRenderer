#include "Model.h"

using namespace Rendering;
using namespace Models;

Model::Model() {}

Model::~Model()
{
	Destroy();
}

void Model::Draw()
{

}

void Model::Draw(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix)
{

}

void Model::Update()
{

}

void Model::SetProgram(GLuint program)
{
	this->m_program = program;
}

GLuint Model::GetVao() const
{
	return m_vao;
}

const std::vector<GLuint>& Model::GetVbos() const
{
	return m_vbos;
}

void Model::Destroy()
{
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(static_cast<int>(m_vbos.size()), &m_vbos[0]);
	m_vbos.clear();
}
