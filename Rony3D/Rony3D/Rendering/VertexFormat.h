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

		VertexFormat(const glm::vec3 &position, const glm::vec4 &color)
		{
			this->position = position;
			this->color = color;
		}

		VertexFormat() {}

	};
}
#endif
