#ifndef INIT_INITGLUT_H
#define INIT_INITGLUT_H

#include <iostream>

#include "ContextInfo.h"
#include "FrameBufferInfo.h"
#include "WindowInfo.h"
#include "IListener.h"

namespace LiteRenderer
{
	namespace Core
	{
		namespace Init
		{
			class InitGLUT
			{
			public:
				static void Init(int argc, char **argv, const WindowInfo& windowInfo, const ContextInfo& contextInfo, const FrameBufferInfo& frameBufferInfo);

			public:
				static void SetListener(IListener* iListener);

				static void Run();
				static void Close();

				static void EnterFullscreen();
				static void ExitFullscreen();

				static void PrintOpenGLInfo(const WindowInfo& windowInfo, const ContextInfo& context);

			private:
				// general callbacks
				static void IdleCallback(void);
				static void CloseCallback();

				// drawing callbacks
				static void DisplayCallback(void);
				static void ReshapeCallback(int width, int height);

				// input callbacks
				static void KeyboardCallback(unsigned char key, int x, int y);
				static void KeyboardUpCallback(unsigned char key, int x, int y);
				static void SpecialKeyboardCallback(int key, int x, int y);
				static void SpecialKeyboardUpCallback(int key, int x, int y);
				static void MouseCallback(int button, int state, int x, int y);
				static void MouseWheelCallback(int button, int state, int x, int y);
				static void MouseMotionCallback(int x, int y);
				static void MousePassiveMotionCallback(int x, int y);

				static IListener*	m_listener;
				static WindowInfo	m_windowInformation;
			};
		}
	}
}

#endif // !INIT_INITGLUT_H

