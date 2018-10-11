#ifndef TEXT_TEXTOBJECT_H
#define TEXT_TEXTOBJECT_H

#include <string>
#include <glm/glm.hpp>

namespace LiteRenderer
{
	namespace Rendering
	{
		namespace Text
		{
			struct TextObject
			{
				int textSize = 48;
				float textScale = 1.0f;
				glm::vec2 textCoords = { 0, 0 };
				glm::vec3 textColor = { 1, 0, 0 };
				std::string textFontname = "";
				std::string textToRender = "";
			};
		}
	}
}

#endif // !RENDERING_TEXTURELOADER_H

