#ifndef ENGINE_H
#define ENGINE_H

#include "Core\Init\InitGLUT.h"
#include "Managers\SceneManager.h"

namespace Rony3D
{
	class Engine
	{
	public:
		Engine();
		~Engine();

		//OpenGL and manager init
		bool Init(int argc, char **argv);

		//Loop
		void Run();

		//Getters
		Managers::SceneManager*  GetSceneManager()  const;
		Managers::ShaderManager* GetShaderManager() const;
		Managers::ModelsManager* GetModelsManager() const;
		TextureLoader* GetTextureLoader() const;

	private:
		Managers::SceneManager*  m_sceneManager  = nullptr;
		Managers::ShaderManager* m_shaderManager = nullptr;
		Managers::ModelsManager* m_modelsManager = nullptr;
		TextureLoader*			 m_textureLoader = nullptr;
	};
}

#endif // !ENGINE_H
