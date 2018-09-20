#ifndef INPUT_INPUTCONTROLLER_H
#define INPUT_INPUTCONTROLLER_H

#include <cstdint>
#include <ctype.h>

namespace LiteRenderer
{
	namespace Core
	{
		namespace Input
		{
			enum class Keys : int
			{
				KEY_W = static_cast<int>('w'),
				KEY_A = static_cast<int>('a'),
				KEY_S = static_cast<int>('s'),
				KEY_D = static_cast<int>('d')
			};

			class InputController
			{
			public:
				static void NormalKeyPressed(unsigned char keyPressed);
				static void SpecialKeyPressed(int keyPressed);

				static void NormalKeyReleased(unsigned char keyReleased);
				static void SpecialKeyReleased(int keyReleased);

				static bool IsNormalKeyPressed(Keys keyPressed);
				static bool IsSpecialKeyPressed(Keys keyPressed);

			private:
				InputController() {}
				~InputController() {}

				static const int MAX_KEYS = 1024;

				static int m_normalKeysPressed[MAX_KEYS];
				static int m_specialKeysPressed[MAX_KEYS];
			};
		}
	}
}

#endif
