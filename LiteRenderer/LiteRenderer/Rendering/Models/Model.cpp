#include "Model.h"

using namespace LiteRenderer;
using namespace Rendering;
using namespace Models;

Model::Model() {}

Model::~Model()
{
	Destroy();
}

void Model::Destroy()
{
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(static_cast<int>(m_vbos.size()), &m_vbos[0]);
	m_vbos.clear();

	if (m_textures.size() > 0)
	{
		for (auto texture : m_textures)
			glDeleteTextures(1, &texture.second);
		m_textures.clear();
	}
}

void Model::Update()
{

}

void Model::Draw(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix)
{

}

void Model::SetProgram(GLuint program)
{
	if (program == 0)
		return;
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

const GLuint Model::GetTexture(const std::string& textureName) const
{
	return m_textures.at(textureName);
}

void Model::AddTexture(const std::string& textureName, GLuint textureId)
{
	if (textureId == 0)
		return;
	m_textures[textureName] = textureId;
}

std::set<GLuint> const &Model::GetCurrentTextures() const
{
	return m_currentTextures;
}

void Model::SetCurrentTextures(const std::set<GLuint>& textures)
{
	m_currentTextures = textures;
}

