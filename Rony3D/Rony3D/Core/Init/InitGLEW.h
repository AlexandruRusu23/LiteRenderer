#ifndef INIT_GLEW_H
#define INIT_GLEW_H

#include <iostream>

#include <glew/glew.h>
#include <freeglut/freeglut.h>

namespace Core
{
	namespace Init
	{
		class InitGLEW
		{
		public:
			InitGLEW(void);
			~InitGLEW(void);

			static void Init();
		};
	}
}

#endif
