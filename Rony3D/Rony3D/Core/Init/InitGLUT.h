#ifndef INIT_GLUT_H
#define INIT_GLUT_H

#include <iostream>

#include "ContextInfo.h"
#include "FrameBufferInfo.h"
#include "WindowInfo.h"
#include "IListener.h"

namespace Core
{
	namespace Init
	{
		class InitGLUT
		{
		public:
			static void Init(const WindowInfo& windowInfo, const ContextInfo& contextInfo, const FrameBufferInfo& frameBufferInfo);
		public:
			static void SetListener(IListener* iListener);

			static void Run();
			static void Close();

			void EnterFullscreen();
			void ExitFullscreen();

			static void PrintOpenGLInfo(const WindowInfo& windowInfo, const ContextInfo& context);
		private:
			static void IdleCallback(void);
			static void DisplayCallback(void);
			static void ReshapeCallback(int width, int height);
			static void CloseCallback();

			static IListener* m_listener;
			static WindowInfo m_windowInformation;
		};
	}
}

#endif
