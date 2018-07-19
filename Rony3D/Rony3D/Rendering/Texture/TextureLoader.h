#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include <string>
#include <glew/glew.h>

#include "BMPHeaders.h"

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

#endif // !TEXTURELOADER_H
