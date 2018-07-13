#include "TextureLoader.h"
#include "TextureLoader.h"

#include <fstream>
#include <iostream>

#include "../../Core/Logging/Logger.h"

using namespace Rendering;

TextureLoader::TextureLoader()
{

}

TextureLoader::~TextureLoader()
{

}

unsigned int TextureLoader::LoadTexture(const std::string& filename, unsigned int width, unsigned int height)
{
	unsigned char* data;
	LoadBMPFile(filename, width, height, data);

	unsigned int textureObject;
	glGenTextures(1, &textureObject);
	glBindTexture(GL_TEXTURE_2D, textureObject);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	
	float maxAnisotropy;
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAnisotropy);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, maxAnisotropy);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	delete data;

	glGenerateMipmap(GL_TEXTURE_2D);

	return textureObject;
}

void TextureLoader::LoadBMPFile(const std::string& filename, unsigned int& width, unsigned int& height, unsigned char*& data)
{
	std::ifstream file(filename.c_str(), std::ios::in | std::ios::binary);
	if (!file.good()) {
		Logger::Log(LogType::ERROR_MESSAGE, "Texture Loader: Cannot open texture file %s", filename.c_str());
		width = 0;
		height = 0;
		return;
	}

	Texture::BMP_Header bmpHeader; 
	Texture::BMP_Header_Info bmpHeaderInfo;
	file.read((char*)&(bmpHeader.type[0]), sizeof(char));
	file.read((char*)&(bmpHeader.type[1]), sizeof(char));
	file.read((char*)&(bmpHeader.f_lenght), sizeof(int));
	file.read((char*)&(bmpHeader.rezerved1), sizeof(short));
	file.read((char*)&(bmpHeader.rezerved2), sizeof(short));
	file.read((char*)&(bmpHeader.offBits), sizeof(int));
	file.read((char*)&(bmpHeaderInfo), sizeof(Texture::BMP_Header_Info));

	data = new unsigned char[bmpHeaderInfo.width*bmpHeaderInfo.height * 3];

	long padd = 0;
	if ((bmpHeaderInfo.width * 3) % 4 != 0) padd = 4 - (bmpHeaderInfo.width * 3) % 4;

	width = bmpHeaderInfo.width;
	height = bmpHeaderInfo.height;

	long pointer;
	unsigned char r, g, b;
	for (unsigned int i = 0; i < height; i++)
	{
		for (unsigned int j = 0; j < width; j++)
		{
			file.read((char*)&b, 1);
			file.read((char*)&g, 1);
			file.read((char*)&r, 1);

			pointer = (i*width + j) * 3;
			data[pointer] = r;
			data[pointer + 1] = g;
			data[pointer + 2] = b;
		}

		file.seekg(padd, std::ios_base::cur);
	}
	file.close();
}
