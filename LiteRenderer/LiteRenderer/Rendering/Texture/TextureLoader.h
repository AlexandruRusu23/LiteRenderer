#ifndef RENDERING_TEXTURELOADER_H
#define RENDERING_TEXTURELOADER_H

#include <string>
#include <glew/glew.h>

#include "BMPHeaders.h"

namespace LiteRenderer
{
	namespace Rendering
	{
		class TextureLoader
		{
		public:
			TextureLoader();
			~TextureLoader();

			unsigned int LoadTexture(const std::string& filename, unsigned int width, unsigned int height);

		private:
			void LoadBMPFile(const std::string& filename, unsigned int& width, unsigned int& height, unsigned char*& data);
		};
	}
}

#endif // !RENDERING_TEXTURELOADER_H

