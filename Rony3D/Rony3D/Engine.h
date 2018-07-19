#ifndef ENGINE_H
#define ENGINE_H

#include "Core/Init/InitGLUT.h"
#include "Managers/SceneManager.h"

namespace RenderEngine
{
	class Engine
	{
	public:
		Engine();
		~Engine();

		bool Init(int argc, char **argv);

		void Run();

		Managers::SceneManager*		GetSceneManager()  const;
		Managers::ShaderManager*	GetShaderManager() const;
		Managers::ModelsManager*	GetModelsManager() const;
		TextureLoader*				GetTextureLoader() const;

	private:
		Managers::SceneManager*		m_sceneManager  = nullptr;
		Managers::ShaderManager*	m_shaderManager = nullptr;
		Managers::ModelsManager*	m_modelsManager = nullptr;
		TextureLoader*				m_textureLoader = nullptr;
	};
}

#endif // !ENGINE_H
