#ifndef WINDOWINFO_H
#define WINDOWINFO_H

#include <iostream>
#include <string>

namespace Core
{
	struct WindowInfo
	{
		std::string name;
		int width;
		int height;
		int positionX;
		int positionY;
		bool isReshapable;

		WindowInfo()
		{
			name = "Rony3D";
			width = 800; height = 600;
			positionX = 300;
			positionY = 300;
			isReshapable = true;
		}

		WindowInfo(std::string name, int startPositionX, int startPositionY, int width, int height, bool isReshapable)
		{
			this->name = name;
			this->width = width;
			this->height = height;
			this->positionX = startPositionX;
			this->positionY = startPositionY;
			this->isReshapable = isReshapable;
		}

		// copy constructor
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

#endif
