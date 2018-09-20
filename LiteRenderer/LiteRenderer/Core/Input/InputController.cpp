#include "InputController.h"

using namespace LiteRenderer::Core::Input;

int InputController::m_normalKeysPressed[MAX_KEYS] = { 0 };
int InputController::m_specialKeysPressed[MAX_KEYS] = { 0 };

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
