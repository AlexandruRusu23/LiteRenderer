#include "CubeIndex.h"

#define PI 3.14159265

using namespace Rendering;
using namespace Models;

CubeIndex::CubeIndex()
{

}

CubeIndex::~CubeIndex()
{

}

void CubeIndex::Create()
{
	GLuint vao;
	GLuint vbo;
	GLuint ibo;

	m_timer = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	std::vector<VertexFormat> vertices;
	std::vector<unsigned int> indices =
	{ 0, 1, 2, 0, 2, 3, //front
	  4, 5, 6, 4, 6, 7, //right
	  8, 9, 10, 8, 10, 11, //back
	  12, 13, 14, 12, 14, 15, //left
	  16, 17, 18, 16, 18, 19, //upper
	  20, 21, 22, 20, 22, 23
	}; //bottom

	//front
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, 1.0), glm::vec4(0, 0, 1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, 1.0), glm::vec4(1, 0, 1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, 1.0), glm::vec4(1, 1, 1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, 1.0), glm::vec4(0, 1, 1, 1)));

	//right
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, 1.0), glm::vec4(1, 1, 1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, -1.0), glm::vec4(1, 1, 0, 1)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, -1.0), glm::vec4(1, 0, 0, 1)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, 1.0), glm::vec4(1, 0, 1, 1)));

	//back
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, -1.0), glm::vec4(0, 0, 0, 1)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, -1.0), glm::vec4(1, 0, 0, 1)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, -1.0), glm::vec4(1, 1, 0, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, -1.0), glm::vec4(0, 1, 0, 1)));

	//left
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, -1.0), glm::vec4(0, 0, 0, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, 1.0), glm::vec4(0, 0, 1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, 1.0), glm::vec4(0, 1, 1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, -1.0), glm::vec4(0, 1, 0, 1)));

	//upper
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, 1.0), glm::vec4(1, 1, 1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, 1.0), glm::vec4(0, 1, 1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, -1.0), glm::vec4(0, 1, 0, 1)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, -1.0), glm::vec4(1, 1, 0, 1)));

	//bottom
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, -1.0), glm::vec4(0, 0, 0, 1)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, -1.0), glm::vec4(1, 0, 0, 1)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, 1.0), glm::vec4(1, 0, 1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, 1.0), glm::vec4(0, 0, 1, 1)));

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VertexFormat), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::color)));
	glBindVertexArray(0);

	this->m_vao = vao;
	this->m_vbos.push_back(vbo);
	this->m_vbos.push_back(ibo);

	m_rotationSpeed = glm::vec3(100.0, 100.0, 100.0);
	m_rotation = glm::vec3(0.0, 0.0, 0.0);
	m_translate = glm::vec3(0.0, 0.0, 0.0);
	m_translateMatrix = glm::translate(glm::mat4(1.0f), m_translate);
}

void CubeIndex::Update()
{
	auto current_miliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
	float deltaTime = static_cast<float>(std::chrono::duration_cast<std::chrono::milliseconds>(current_miliseconds - m_timer).count());
	float fps = 1000.f / deltaTime;

	m_rotation = (1.f / fps) * m_rotationSpeed + m_rotation;

	m_timer = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
}

void CubeIndex::Draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix)
{
	glm::vec3 rotation_sin = glm::vec3(m_rotation.x * PI / 180, m_rotation.y * PI / 180, m_rotation.z * PI / 180);

	glUseProgram(m_program);
	glUniform3f(glGetUniformLocation(m_program, "rotation"), rotation_sin.x, rotation_sin.y, rotation_sin.z);
	glUniformMatrix4fv(glGetUniformLocation(m_program, "translate_matrix"), 1, GL_FALSE, &m_translateMatrix[0][0]);

	glUniformMatrix4fv(glGetUniformLocation(m_program, "view_matrix"), 1, GL_FALSE, &view_matrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(m_program, "projection_matrix"), 1, GL_FALSE, &projection_matrix[0][0]);
	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}
