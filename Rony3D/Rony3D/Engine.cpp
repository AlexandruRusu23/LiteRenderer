#include "Engine.h"

#include "Rendering\Camera\PerspectiveCamera.h"

using namespace RenderEngine;
using namespace Core;

Engine::Engine()
{

}

Engine::~Engine()
{
	if (m_sceneManager)
		delete m_sceneManager;

	if (m_shaderManager)
		delete m_shaderManager;

	if (m_modelsManager)
		delete m_modelsManager;

	if (m_textureLoader)
		delete m_textureLoader;
}

bool Engine::Init(int argc, char **argv)
{
	WindowInfo windowInfo(std::string("Rony3D"), 200, 100, 1280, 720, true);
	ContextInfo contextInfo(4, 3, true);
	FrameBufferInfo frameBufferInfo(true, true, true, true);
	Init::InitGLUT::Init(argc, argv, windowInfo, contextInfo, frameBufferInfo);

	m_sceneManager = new Managers::SceneManager();
	Init::InitGLUT::SetListener(m_sceneManager);

	m_shaderManager = new Managers::ShaderManager();
	m_textureLoader = new TextureLoader();
	
	if (m_sceneManager && m_shaderManager)
	{
		m_modelsManager = new Managers::ModelsManager();
		m_camera = new Rendering::Camera::PerspectiveCamera();
		m_sceneManager->SetModelsManager(m_modelsManager);
		m_sceneManager->SetCamera(m_camera);
	}
	else
		return false;

	return true;
}

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

TextureLoader* Engine::GetTextureLoader() const
{
	return m_textureLoader;
}
