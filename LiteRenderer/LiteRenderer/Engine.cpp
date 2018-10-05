#include "Engine.h"

#include "Rendering\Camera\PerspectiveCamera.h"

using namespace LiteRenderer;

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

	if (m_textManager)
		delete m_textManager;

	if (m_textureLoader)
		delete m_textureLoader;

	if (m_camera)
		delete m_camera;
}

void Engine::Init(int argc, char **argv)
{
	Core::WindowInfo windowInfo(std::string("LiteRenderer"), 200, 100, 1280, 720, true);
	Core::ContextInfo contextInfo(4, 3, true);
	Core::FrameBufferInfo frameBufferInfo(true, true, true, true);
	Core::Init::InitGLUT::Init(argc, argv, windowInfo, contextInfo, frameBufferInfo);

	m_sceneManager = new Managers::SceneManager();
	m_shaderManager = new Managers::ShaderManager();
	m_textureLoader = new Rendering::TextureLoader();
	m_modelsManager = new Managers::ModelsManager();
	m_textManager = new Managers::TextManager();
	m_camera = new Rendering::Camera::PerspectiveCamera();
	
	Core::Init::InitGLUT::SetListener(m_sceneManager);
	m_sceneManager->SetModelsManager(m_modelsManager);
	m_sceneManager->SetCamera(m_camera);

	m_textManager->SetModelsManager(m_modelsManager);
}

void Engine::Run()
{
	Core::Init::InitGLUT::Run();
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

Managers::TextManager* Engine::GetTextManager()	const
{
	return m_textManager;
}

Rendering::TextureLoader* Engine::GetTextureLoader() const
{
	return m_textureLoader;
}

