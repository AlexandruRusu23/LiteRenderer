#include "SceneManager.h"

using namespace Managers;

SceneManager::SceneManager()
{
	glEnable(GL_DEPTH_TEST);

	m_viewMatrix = glm::mat4(	1.0f, 0.0f, 0.0f,  0.0f,
								0.0f, 1.0f, 0.0f,  0.0f,
								0.0f, 0.0f, -1.0f, 0.0f,
								0.0f, 0.0f, 5.0f, 1.0f);
}

SceneManager::~SceneManager()
{
	delete m_shaderManager;
	delete m_modelsManager;
}

void SceneManager::NotifyBeginFrame()
{
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

void SceneManager::SetModelsManager(ModelsManager*& modelsManager)
{
	m_modelsManager = modelsManager;
}
