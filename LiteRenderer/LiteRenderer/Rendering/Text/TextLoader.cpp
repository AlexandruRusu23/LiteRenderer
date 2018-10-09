#include "TextLoader.h"

#include <assert.h>

#include "Logger.h"

using namespace LiteRenderer;
using namespace Rendering;
using namespace Text;

TextLoader::TextLoader()
	: Singleton()
{
	assert(!m_ftLibrary);
	if (FT_Init_FreeType(&m_ftLibrary))
	{
		Logger::Log("ERROR::FREETYPE: Could not init FreeType library");
		assert(false);
		return;
	}
}

TextLoader::~TextLoader()
{
	FT_Done_FreeType(m_ftLibrary);
}

void TextLoader::LoadFont(std::string fontName, std::string fontFilename, unsigned int fontSize)
{
	FT_Face ftFace;
	if (FT_New_Face(m_ftLibrary, fontFilename.c_str(), 0, &ftFace))
		Logger::Log("ERROR::FREETYPE: Failed to load font at: %s", fontFilename);

	FT_Set_Pixel_Sizes(ftFace, 0, fontSize);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	for (unsigned char c = 0; c < 128; c++)
	{
		if (FT_Load_Char(ftFace, c, FT_LOAD_RENDER))
		{
			Logger::Log("ERROR::FREETYTPE: Failed to load Glyph: %c", c);
			continue;
		}

		if (c == ' ')
		{
			ftFace->glyph->bitmap.width = 1;
			ftFace->glyph->bitmap.rows = 1;
		}

		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D, 
			0, 
			GL_RED, 
			ftFace->glyph->bitmap.width, 
			ftFace->glyph->bitmap.rows, 
			0, 
			GL_RED, 
			GL_UNSIGNED_BYTE, 
			ftFace->glyph->bitmap.buffer
		);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
		FTCharacter character = {
			texture,
			glm::ivec2(ftFace->glyph->bitmap.width, ftFace->glyph->bitmap.rows),
			glm::ivec2(ftFace->glyph->bitmap_left, ftFace->glyph->bitmap_top),
			static_cast<unsigned int>(ftFace->glyph->advance.x)
		};
		m_fontCharactersList[fontName].insert({c, character});
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	FT_Done_Face(ftFace);
}

const std::map<char, TextLoader::FTCharacter> TextLoader::GetFontCharacters(std::string fontName) const
{
	return m_fontCharactersList.at(fontName);
}

const TextLoader::FTCharacter TextLoader::GetFontCharacter(std::string fontName, char character) const
{
	if (m_fontCharactersList.find(fontName) != m_fontCharactersList.end())
		return m_fontCharactersList.at(fontName).at(character);

	return FTCharacter();
}

