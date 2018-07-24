#ifndef CORE_ILISTENER_H
#define CORE_ILISTENER_H

namespace LiteRenderer
{
	namespace Core
	{
		class IListener
		{
		public:
			virtual ~IListener() = 0;

			//drawing functions
			virtual void NotifyBeginFrame() = 0;
			virtual void NotifyDisplayFrame() = 0;
			virtual void NotifyEndFrame() = 0;
			virtual void NotifyReshape(int width, int height, int previousWidth, int previousHeight) = 0;

			//input functions
			virtual void NotifyKeyboardPressed(unsigned char key, int x, int y) = 0;
			virtual void NotifyKeyboardReleased(unsigned char key, int x, int y) = 0;
			virtual void NotifySpecialKeyboardPressed(int key, int x, int y) = 0;
			virtual void NotifySpecialKeyboardReleased(int key, int x, int y) = 0;
			virtual void NotifyMouse(int button, int state, int x, int y) = 0;
			virtual void NotifyMouseWheel(int button, int state, int x, int y) = 0;
			virtual void NotifyMouseMotion(int x, int y) = 0;
			virtual void NotifyMousePassiveMotion(int x, int y) = 0;
		};

		inline IListener::~IListener()
		{

		}
	}
}

#endif // !CORE_ILISTENER_H

