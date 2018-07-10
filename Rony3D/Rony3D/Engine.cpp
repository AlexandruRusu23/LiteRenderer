#include "Engine.h"

using namespace Rony3D;
using namespace Core;

Engine::Engine()
{

}

bool Engine::Init(int argc, char **argv)
{
	WindowInfo windowInfo(std::string("Rony3D"), 300, 300, 800, 600, true);
	ContextInfo contextInfo(3, 3, true);
	FrameBufferInfo frameBufferInfo(true, true, true, true);
	Init::InitGLUT::Init(argc, argv, windowInfo, contextInfo, frameBufferInfo);

	m_sceneManager = new Managers::SceneManager();
	Init::InitGLUT::SetListener(m_sceneManager);

	m_shaderManager = new Managers::ShaderManager();

	if (m_sceneManager && m_shaderManager)
	{
		m_modelsManager = new Managers::ModelsManager();
		m_sceneManager->SetModelsManager(m_modelsManager);
	}
	else
	{
		return false;
	}

	return true;
}

//Create the loop
void Engine::Run()
{
	Init::InitGLUT::Run();
}

Managers::SceneManager* Engine::GetSceneManager() const
{
	return m_sceneManager;
}

Managers::ShaderManager* Engine::GetShaderManager() const
{
	return m_shaderManager;
}

Managers::ModelsManager* Engine::GetModelsManager() const
{
	return m_modelsManager;
}

Engine::~Engine()
{
	if (m_sceneManager)
		delete m_sceneManager;

	if (m_shaderManager)
		delete m_shaderManager;

	if (m_modelsManager)
		delete m_modelsManager;
}
