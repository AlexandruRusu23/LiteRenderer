#ifndef INPUT_INPUTCONTROLLER_H
#define INPUT_INPUTCONTROLLER_H

#include <freeglut\freeglut.h>
#include <utility>
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

			enum class MouseButton : int
			{
				LEFT_CLICK = GLUT_LEFT_BUTTON,
				MIDDLE_CLICK = GLUT_MIDDLE_BUTTON,
				RIGHT_CLICK = GLUT_RIGHT_BUTTON
			};

			enum class MouseScroll : int
			{
				SCROLL_DOWN = GLUT_DOWN,
				SCROLL_UP = GLUT_UP,
				NO_SCROLL
			};

			class InputController
			{
			public:
				InputController() = delete;
				~InputController() = delete;
				InputController(InputController& inputController) = delete;
				InputController& operator=(const InputController& inputController) = delete;

				static void UpdateInput();

				static void NormalKeyPressed(unsigned char keyPressed);
				static void SpecialKeyPressed(int keyPressed);

				static void NormalKeyReleased(unsigned char keyReleased);
				static void SpecialKeyReleased(int keyReleased);

				static bool IsNormalKeyPressed(Keys keyPressed);
				static bool IsSpecialKeyPressed(Keys keyPressed);

				static void MouseButtonEvent(int button, int state, int x, int y);
				static void MouseScrolling(int button, int state, int x, int y);
				static void MouseMovingReleased(int x, int y);
				static void MouseMovingPressed(int x, int y);

				static bool IsMousePressed();
				static bool IsMouseButtonPressed(MouseButton button);
				static MouseScroll GetMouseScroll();
				static std::pair<int, int> GetMousePosition();
				static std::pair<int, int> GetMousePressedDeltaPosition();
				static std::pair<int, int> GetMouseReleasedDeltaPosition();
				static std::pair<float, float> GetMouseSensitivity();

			private:
				static const int MAX_KEYS = 1024;
				static const int MAX_BUTTONS = 64;

				static int m_normalKeysPressed[MAX_KEYS];
				static int m_specialKeysPressed[MAX_KEYS];
				static int m_mouseButtonsPressed[MAX_BUTTONS];

				static bool m_mousePressed;
				static MouseScroll m_mouseScroll;

				static std::pair<int, int> m_mousePosition;
				static std::pair<int, int> m_mousePressedDeltaPosition;
				static std::pair<int, int> m_mouseReleasedDeltaPosition;
				static std::pair<float, float> m_mouseSensitivity;
			};
		}
	}
}

#endif // !INPUT_INPUTCONTROLLER_H

