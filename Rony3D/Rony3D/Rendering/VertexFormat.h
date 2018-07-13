#ifndef VERTEXFORMAT_H
#define VERTEXFORMAT_H

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace Rendering
{
	struct VertexFormat
	{
		glm::vec3 position;
		glm::vec4 color;
		glm::vec2 texture;

		VertexFormat() = delete;

		VertexFormat(const glm::vec3 &position, const glm::vec4 &color)
		{
			this->position = position;
			this->color = color;
			texture.x = texture.y = 0;
		}

		VertexFormat(const glm::vec3 &position, const glm::vec2 &texture)
		{
			this->position = position;
			this->color = { 0, 0, 0, 1};
			this->texture = texture;
		}
	};
}
#endif
