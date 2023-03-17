#include "TextModel.h"

using namespace LiteRenderer;
using namespace Rendering;
using namespace Text;

TextModel::TextModel()
{

}

TextModel::~TextModel()
{

}

void TextModel::Create()
{
	GLuint vao;
	GLuint vbo;

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)0);
	glBindVertexArray(0);

	this->m_vao = vao;
	this->m_vbos.push_back(vbo);
}

void TextModel::SetTextObject(const TextObject& textObject)
{
	m_textObject = textObject;
}

void TextModel::Update()
{

}

void TextModel::Draw(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix)
{
	glUseProgram(m_program);
	glBindVertexArray(m_vao);
	
	glActiveTexture(GL_TEXTURE0);

	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(glutGet(GLUT_SCREEN_WIDTH)), 0.0f, static_cast<float>(glutGet(GLUT_SCREEN_HEIGHT)));
	glUniformMatrix4fv(glGetUniformLocation(m_program, "projection_matrix"), 1, GL_FALSE, &projection[0][0]);
	glUniform3f(glGetUniformLocation(m_program, "textColor"), m_textObject.textColor.x, m_textObject.textColor.y, m_textObject.textColor.z);

	float xTextCoords = m_textObject.textCoords.x;
	float yTextCoords = m_textObject.textCoords.y;

	for (auto cter : m_textObject.textToRender)
	{
		TextLoader::FTCharacter ch = TextLoader::Instance().GetFontCharacter(m_textObject.textFontname, cter);

		float xPos = xTextCoords + ch.bearing.x * m_textObject.textScale;
		float yPos = yTextCoords - (ch.size.y - ch.bearing.y) * m_textObject.textScale;

		float width = ch.size.x * m_textObject.textScale;
		float height = ch.size.y * m_textObject.textScale;

		float vertices[6][4] = {
			{ xPos,			yPos + height,	0.0, 0.0 },
			{ xPos,			yPos,			0.0, 1.0 },
			{ xPos + width, yPos,			1.0, 1.0 },

			{ xPos,			yPos + height,	0.0, 0.0 },
			{ xPos + width, yPos,			1.0, 1.0 },
			{ xPos + width, yPos + height,	1.0, 0.0 }
		};

		glBindTexture(GL_TEXTURE_2D, ch.textureID);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbos[0]);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		
		xTextCoords += (ch.advance >> 6) * m_textObject.textScale;
	}
}

