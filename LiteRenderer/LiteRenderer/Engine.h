#ifndef LITERENDERER_ENGINE_H
#define LITERENDERER_ENGINE_H

#include <memory>

#include "Core/Init/InitGLUT.h"
#include "Managers/SceneManager.h"
#include "Rendering/ICamera.h"

namespace LiteRenderer
{
	class Engine
	{
	public:
		Engine();
		~Engine();

		void Init(int argc, char **argv);

		void Run();

		Managers::SceneManager&		GetSceneManager()	const;
		Managers::ShaderManager&	GetShaderManager()	const;
		Rendering::TextureLoader&	GetTextureLoader()	const;
		std::shared_ptr<Managers::ModelsManager>	GetModelsManager()	const;
		std::shared_ptr<Rendering::ICamera>	GetCamera()	const;

	private:
		std::unique_ptr<Managers::SceneManager>		m_sceneManager;
		std::unique_ptr<Managers::ShaderManager>	m_shaderManager;
		std::unique_ptr<Rendering::TextureLoader>	m_textureLoader;
		std::shared_ptr<Managers::ModelsManager>	m_modelsManager;
		std::shared_ptr<Rendering::ICamera>			m_camera;
	};
}

#endif // !LITERENDERER_ENGINE_H

