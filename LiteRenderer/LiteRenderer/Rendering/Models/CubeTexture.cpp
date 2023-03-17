#include "CubeTexture.h"

#include "Timer.h"

using namespace LiteRenderer;
using namespace Rendering;
using namespace Models;

const float CubeTexture::PI = 3.14159265f;

CubeTexture::CubeTexture()
	: m_rotation(glm::vec3())
	, m_rotationSpeed(glm::vec3())
	, m_rotationSin(glm::vec3())
	, m_translate(glm::vec3())
	, m_translateMatrix(glm::mat4())
{

}

CubeTexture::~CubeTexture()
{

}

void CubeTexture::Create()
{
	GLuint vao;
	GLuint vbo;
	GLuint ibo;

	std::vector<VertexFormat> vertices;
	std::vector<unsigned int> indices =
	{ 0, 1, 2, 0, 2, 3, //front
	  4, 5, 6, 4, 6, 7, //right
	  8, 9, 10, 8, 10, 11, //back
	  12, 13, 14, 12, 14, 15, //left
	  16, 17, 18, 16, 18, 19, //upper
	  20, 21, 22, 20, 22, 23 //bottom
	};

	//front
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, 1.0), glm::vec2(0, 0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, 1.0), glm::vec2(1, 0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, 1.0), glm::vec2(1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, 1.0), glm::vec2(0, 1)));

	//right
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, 1.0), glm::vec2(0, 0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, -1.0), glm::vec2(1, 0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, -1.0), glm::vec2(1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, 1.0), glm::vec2(0, 1)));

	//back
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, -1.0), glm::vec2(0, 0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, -1.0), glm::vec2(1, 0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, -1.0), glm::vec2(1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, -1.0), glm::vec2(0, 1)));

	//left
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, -1.0), glm::vec2(0, 0)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, 1.0), glm::vec2(1, 0)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, 1.0), glm::vec2(1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, -1.0), glm::vec2(0, 1)));

	//upper
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, 1.0), glm::vec2(0, 0)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, 1.0), glm::vec2(1, 0)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, -1.0), glm::vec2(1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, -1.0), glm::vec2(0, 1)));

	//bottom
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, -1.0), glm::vec2(0, 0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, -1.0), glm::vec2(1, 0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, 1.0), glm::vec2(1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, 1.0), glm::vec2(0, 1)));

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VertexFormat), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::texture)));
	glBindVertexArray(0);

	this->m_vao = vao;
	this->m_vbos.push_back(vbo);
	this->m_vbos.push_back(ibo);

	static int x = 0;

	m_rotationSpeed = glm::vec3(0.0, 0.0, 0.0);
	m_rotation = glm::vec3(0.0, 0.0, 0.0);
	m_translate = glm::vec3(3.0 * x, 0.0, 0.0);
	
	x++;

	m_translateMatrix = glm::translate(glm::mat4(1.0f), m_translate);
}

void CubeTexture::Update()
{
	m_rotation = Utils::Timer::GetDeltaTime() * m_rotationSpeed + m_rotation;
	m_rotationSin = glm::vec3(m_rotation.x * PI / 180, m_rotation.y * PI / 180, m_rotation.z * PI / 180);
}

void CubeTexture::Draw(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix)
{
	glUseProgram(m_program);
	glBindVertexArray(m_vao);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, *this->GetCurrentTextures().begin());

	// fragment shader data
	glUniform1i(glGetUniformLocation(m_program, "texture_sampler"), 0);

	// vertex shader data
	glUniformMatrix4fv(glGetUniformLocation(m_program, "projection_matrix"), 1, GL_FALSE, &projectionMatrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(m_program, "view_matrix"), 1, GL_FALSE, &viewMatrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(m_program, "translate_matrix"), 1, GL_FALSE, &m_translateMatrix[0][0]);
	glUniform3f(glGetUniformLocation(m_program, "rotation"), m_rotationSin.x, m_rotationSin.y, m_rotationSin.z);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

