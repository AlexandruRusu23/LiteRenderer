#include "InputController.h"

using namespace LiteRenderer::Core::Input;

int InputController::m_normalKeysPressed[MAX_KEYS] = { 0 };
int InputController::m_specialKeysPressed[MAX_KEYS] = { 0 };
int InputController::m_mouseButtonsPressed[MAX_BUTTONS] = { 0 };

bool InputController::m_mousePressed = false;
MouseScroll InputController::m_mouseScroll = MouseScroll::NO_SCROLL;

std::pair<int, int> InputController::m_mousePosition = { 0, 0 };
std::pair<int, int> InputController::m_mousePressedDeltaPosition = { 0, 0 };
std::pair<int, int> InputController::m_mouseReleasedDeltaPosition = { 0, 0 };
std::pair<float, float> InputController::m_mouseSensitivity = { 0.0020f, 0.0020f };

void InputController::NormalKeyPressed(unsigned char keyPressed)
{
	m_normalKeysPressed[tolower(keyPressed)] = true;
}

void InputController::SpecialKeyPressed(int keyPressed)
{
	m_specialKeysPressed[keyPressed] = true;
}

void InputController::NormalKeyReleased(unsigned char keyReleased)
{
	m_normalKeysPressed[tolower(keyReleased)] = false;
}

void InputController::SpecialKeyReleased(int keyReleased)
{
	m_specialKeysPressed[keyReleased] = false;
}

bool InputController::IsNormalKeyPressed(Keys keyPressed)
{
	return m_normalKeysPressed[static_cast<int>(keyPressed)] ? true : false;
}

bool InputController::IsSpecialKeyPressed(Keys keyPressed)
{
	return m_specialKeysPressed[static_cast<int>(keyPressed)] ? true : false;
}

void InputController::MouseButtonEvent(int button, int state, int x, int y)
{
	m_mousePosition = { x, y };

	if (state == GLUT_DOWN)
	{
		m_mousePressed = true;
		m_mouseButtonsPressed[button] = true;
	}
	else
	{
		m_mousePressed = false;
		m_mouseButtonsPressed[button] = false;
	}
}

void InputController::MouseScrolling(int button, int state, int x, int y)
{
	m_mouseScroll = static_cast<MouseScroll>(state);
	m_mousePosition = { x, y };
}

void InputController::MouseMovingReleased(int x, int y)
{
	m_mouseReleasedDeltaPosition = { x - m_mousePosition.first, y - m_mousePosition.second };
	m_mousePosition = { x, y };
}

void InputController::MouseMovingPressed(int x, int y)
{
	m_mousePressedDeltaPosition = { x - m_mousePosition.first, y - m_mousePosition.second };
	m_mousePosition = { x, y };
}

bool InputController::IsMousePressed()
{
	return m_mousePressed;
}

bool InputController::IsMouseButtonPressed(MouseButton button)
{
	return m_mouseButtonsPressed[static_cast<int>(button)] ? true : false;
}

MouseScroll InputController::GetMouseScroll()
{
	return m_mouseScroll;
}

std::pair<int, int> InputController::GetMousePosition()
{
	return m_mousePosition;
}

std::pair<int, int> InputController::GetMousePressedDeltaPosition()
{
	return m_mousePressedDeltaPosition;
}

std::pair<int, int> InputController::GetMouseReleasedDeltaPosition()
{
	return m_mouseReleasedDeltaPosition;
}

std::pair<float, float> InputController::GetMouseSensitivity()
{
	return m_mouseSensitivity;
}

