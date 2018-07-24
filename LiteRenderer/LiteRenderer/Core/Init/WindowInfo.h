#ifndef CORE_WINDOWINFO_H
#define CORE_WINDOWINFO_H

#include <string>

namespace LiteRenderer
{
	namespace Core
	{
		struct WindowInfo
		{
			std::string		name;
			int				width;
			int				height;
			int				positionX;
			int				positionY;
			bool			isReshapable;

			WindowInfo() = delete;

			WindowInfo(std::string name, int startPositionX, int startPositionY, int width, int height, bool isReshapable)
			{
				this->name = name;
				this->width = width;
				this->height = height;
				this->positionX = startPositionX;
				this->positionY = startPositionY;
				this->isReshapable = isReshapable;
			}

			WindowInfo(const WindowInfo& windowInfo)
			{
				this->name = windowInfo.name;
				this->positionX = windowInfo.positionX;
				this->positionY = windowInfo.positionY;
				this->width = windowInfo.width;
				this->height = windowInfo.height;
				this->isReshapable = windowInfo.isReshapable;
			}

			void operator=(const WindowInfo& windowInfo)
			{
				this->name = windowInfo.name;
				this->positionX = windowInfo.positionX;
				this->positionY = windowInfo.positionY;
				this->width = windowInfo.width;
				this->height = windowInfo.height;
				this->isReshapable = windowInfo.isReshapable;
			}
		};
	}
}

#endif // !CORE_WINDOWINFO_H

