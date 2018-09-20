#include "SceneManager.h"

#include "Timer.h"
#include "InputController.h"

using namespace LiteRenderer;
using namespace Managers;

SceneManager::SceneManager()
{
	glEnable(GL_DEPTH_TEST);
	m_viewMatrix = glm::mat4(1.0f);
}

SceneManager::~SceneManager() { }

void SceneManager::NotifyBeginFrame()
{
	Utils::Timer::Update();
	m_modelsManager->Update();
}

void SceneManager::NotifyDisplayFrame()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);

	m_modelsManager->Draw();
	m_modelsManager->Draw(m_projectionMatrix, m_viewMatrix);
}

void SceneManager::NotifyEndFrame()
{
	m_viewMatrix = m_camera->GetViewMatrix();
}

void SceneManager::NotifyReshape(int width, int height, int previous_width, int previous_height)
{
	float ar = (float)glutGet(GLUT_WINDOW_WIDTH) / (float)glutGet(GLUT_WINDOW_HEIGHT);
	float angle = 45.0f, near1 = 0.1f, far1 = 2000.0f;

	m_projectionMatrix[0][0] = 1.0f / (ar * tan(angle / 2.0f));
	m_projectionMatrix[1][1] = 1.0f / tan(angle / 2.0f);
	m_projectionMatrix[2][2] = (-near1 - far1) / (near1 - far1);
	m_projectionMatrix[2][3] = 1.0f;
	m_projectionMatrix[3][2] = 2.0f * near1 * far1 / (near1 - far1);
}

void SceneManager::NotifyKeyboardPressed(unsigned char key, int x, int y)
{
	//Logger::Log("NotifyKeyboardPressed key: %c ;x: %d; y: %d", key, x, y);
	Core::Input::InputController::NormalKeyPressed(key);
	m_camera->KeyPressed(key);
}

void SceneManager::NotifyKeyboardReleased(unsigned char key, int x, int y)
{
	//Logger::Log("NotifyKeyboardReleased key: %c ;x: %d; y: %d", key, x, y);
	Core::Input::InputController::NormalKeyReleased(key);
}

void SceneManager::NotifySpecialKeyboardPressed(int key, int x, int y)
{
	//Logger::Log("NotifySpecialKeyboardPressed key: %d ;x: %d; y: %d", key, x, y);
	Core::Input::InputController::SpecialKeyPressed(key);
}

void SceneManager::NotifySpecialKeyboardReleased(int key, int x, int y)
{
	//Logger::Log("NotifySpecialKeyboardReleased key: %d ;x: %d; y: %d", key, x, y);
	Core::Input::InputController::SpecialKeyReleased(key);
}

void SceneManager::NotifyMouse(int button, int state, int x, int y)
{
	//Logger::Log("NotifyMouse button: %d; state: %d; x: %d; y: %d", button, state, x, y);
	m_camera->MousePressed(button, state, x, y);
}

void SceneManager::NotifyMouseWheel(int button, int state, int x, int y)
{
	//Logger::Log("NotifyMouseWheel button: %d; state: %d; x: %d; y: %d", button, state, x, y);
}

void SceneManager::NotifyMouseMotion(int x, int y)
{
	//Logger::Log("NotifyMouseMotion x: %d; y: %d", x, y);
	m_camera->MouseMove(x, y);
}

void SceneManager::NotifyMousePassiveMotion(int x, int y)
{
	//Logger::Log("NotifyMousePassiveMotion x: %d; y: %d", x, y);
}

void SceneManager::SetModelsManager(ModelsManager*& modelsManager)
{
	m_modelsManager = modelsManager;
}

void Managers::SceneManager::SetCamera(Rendering::ICamera * camera)
{
	m_camera = camera;
}

