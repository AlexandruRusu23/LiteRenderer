#ifndef INIT_INITGLEW_H
#define INIT_INITGLEW_H

#include <iostream>

#include <glew/glew.h>
#include <freeglut/freeglut.h>

namespace LiteRenderer
{
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
}

#endif // !INIT_INITGLEW_H

