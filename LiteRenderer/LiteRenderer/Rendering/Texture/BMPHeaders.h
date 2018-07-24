#ifndef TEXTURE_BMPHEADERS_H
#define TEXTURE_BMPHEADERS_H

namespace LiteRenderer
{
	namespace Rendering
	{
		namespace Texture
		{
			struct BMP_Header
			{
				unsigned char type[2];
				int f_lenght;
				short rezerved1;
				short rezerved2;
				int offBits;
			};

			struct BMP_Header_Info
			{
				int size;
				int width;
				int height;
				short planes;
				short bitCount;
				int compresion;
				int sizeImage;
				int xPelsPerMeter;
				int yPelsPerMeter;
				int clrUsed;
				int clrImportant;
			};
		}
	}
}

#endif // !TEXTURE_BMPHEADERS_H

