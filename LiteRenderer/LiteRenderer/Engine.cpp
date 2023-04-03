#include "Engine.h"

#include "Rendering\Camera\PerspectiveCamera.h"

using namespace LiteRenderer;

Engine::Engine()
{
}

Engine::~Engine()
{
}

void Engine::Init(int argc, char **argv)
{
	Core::WindowInfo windowInfo(std::string("LiteRenderer"), 200, 100, 1280, 720, true);
	Core::ContextInfo contextInfo(4, 3, true);
	Core::FrameBufferInfo frameBufferInfo(true, true, true, true);
	Core::Init::InitGLUT::Init(argc, argv, windowInfo, contextInfo, frameBufferInfo);

	m_sceneManager = std::make_unique<Managers::SceneManager>();
	m_shaderManager = std::make_unique<Managers::ShaderManager>();
	m_textureLoader = std::make_unique<Rendering::TextureLoader>();
	m_modelsManager = std::make_shared<Managers::ModelsManager>();
	m_camera = std::make_unique<Rendering::Camera::PerspectiveCamera>();
	
	Core::Init::InitGLUT::SetListener(m_sceneManager.get());
	m_sceneManager->SetModelsManager(m_modelsManager);
	m_sceneManager->SetCamera(m_camera);
}

void Engine::Run()
{
	Core::Init::InitGLUT::Run();
}

Managers::SceneManager& Engine::GetSceneManager() const
{
	return *m_sceneManager;
}

Managers::ShaderManager& Engine::GetShaderManager() const
{
	return *m_shaderManager;
}

Rendering::TextureLoader& Engine::GetTextureLoader() const
{
	return *m_textureLoader;
}

std::shared_ptr<Managers::ModelsManager> Engine::GetModelsManager() const
{
	return m_modelsManager;
}

std::shared_ptr<Rendering::ICamera> Engine::GetCamera() const
{
	return m_camera;
}

