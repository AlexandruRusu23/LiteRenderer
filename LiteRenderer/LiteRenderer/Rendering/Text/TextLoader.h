#ifndef TEXT_TEXTLOADER_H
#define TEXT_TEXTLOADER_H

#include <string>
#include <map>
#include <glm/glm.hpp>
#include <glew\glew.h>
#include <freeglut\freeglut.h>
#include <ft2build.h>
#include <freetype.h>
#include FT_FREETYPE_H

#include "Utils/Singleton.h"

namespace LiteRenderer
{
	namespace Rendering
	{
		namespace Text
		{
			class TextLoader : public Utils::Singleton<TextLoader>
			{
			public:
				struct FTCharacter
				{
					unsigned int textureID;
					glm::ivec2 size;
					glm::ivec2 bearing;
					unsigned int advance;
				};

			public:
				TextLoader();
				~TextLoader();
				
				void LoadFont(std::string fontName, std::string fontFilename, unsigned int fontSize);
				
				const std::map<char, FTCharacter> GetFontCharacters(std::string fontName) const;
				const FTCharacter GetFontCharacter(std::string fontName, char character) const;

			private:
				FT_Library m_ftLibrary;
				std::map<std::string, std::map<char, FTCharacter>> m_fontCharactersList;
			};
		}
	}
}

#endif // !TEXT_TEXTLOADER_H

