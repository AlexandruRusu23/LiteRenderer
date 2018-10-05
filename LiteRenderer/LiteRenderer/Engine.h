#ifndef LITERENDERER_ENGINE_H
#define LITERENDERER_ENGINE_H

#include "Core/Init/InitGLUT.h"
#include "Managers/SceneManager.h"
#include "Managers/TextManager.h"
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

		Managers::SceneManager*		GetSceneManager()	const;
		Managers::ShaderManager*	GetShaderManager()	const;
		Managers::ModelsManager*	GetModelsManager()	const;
		Managers::TextManager*		GetTextManager()	const;
		Rendering::TextureLoader*	GetTextureLoader()	const;

	private:
		Managers::SceneManager*		m_sceneManager  = nullptr;
		Managers::ShaderManager*	m_shaderManager = nullptr;
		Managers::ModelsManager*	m_modelsManager = nullptr;
		Managers::TextManager*		m_textManager	= nullptr;
		Rendering::TextureLoader*	m_textureLoader = nullptr;
		Rendering::ICamera*			m_camera		= nullptr;
	};
}

#endif // !LITERENDERER_ENGINE_H

