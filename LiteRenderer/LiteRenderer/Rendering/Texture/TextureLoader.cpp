#include "TextureLoader.h"

#include <fstream>

#include "Logger.h"

using namespace LiteRenderer;
using namespace Rendering;

TextureLoader::TextureLoader()
{

}

TextureLoader::~TextureLoader()
{

}

unsigned int TextureLoader::LoadTexture(const std::string& filename)
{
	std::unique_ptr<unsigned char[]> data;
	unsigned int width = 0;
	unsigned int height = 0;
	LoadBMPFile(filename, width, height, data);

	unsigned int textureObject;
	glGenTextures(1, &textureObject);
	glBindTexture(GL_TEXTURE_2D, textureObject);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	float maxAnisotropy;
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAnisotropy);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, maxAnisotropy);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data.get());

	glGenerateMipmap(GL_TEXTURE_2D);

	return textureObject;
}

unsigned int TextureLoader::LoadCubemapTexture(const std::vector<std::string>& filenames)
{
	unsigned int textureObject;
	glGenTextures(1, &textureObject);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureObject);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	unsigned int width = 0;
	unsigned int height = 0;
	std::unique_ptr<unsigned char[]> data;
	for (unsigned int iter = 0; iter < filenames.size(); iter++)
	{
		LoadBMPFile(filenames[iter], width, height, data);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + iter, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data.get());
	}

	return textureObject;
}

void TextureLoader::LoadBMPFile(const std::string& filename, unsigned int& width, unsigned int& height, std::unique_ptr<unsigned char[]> &data)
{
	std::ifstream file(filename.c_str(), std::ios::in | std::ios::binary);
	if (!file.good()) {
		Logger::Log("Texture Loader: Cannot open texture file %s", filename.c_str());
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

	data = std::make_unique<unsigned char[]>(static_cast<size_t>(bmpHeaderInfo.width) * bmpHeaderInfo.height * 3);

	long padd = 0;
	if ((bmpHeaderInfo.width * 3) % 4 != 0) padd = 4 - (bmpHeaderInfo.width * 3) % 4;

	width = bmpHeaderInfo.width;
	height = bmpHeaderInfo.height;

	unsigned int pointer;
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
			data[static_cast<size_t>(pointer) + 1] = g;
			data[static_cast<size_t>(pointer) + 2] = b;
		}

		file.seekg(padd, std::ios_base::cur);
	}
	file.close();
}

