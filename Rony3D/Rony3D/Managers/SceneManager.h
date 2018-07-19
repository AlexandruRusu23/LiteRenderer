#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "ShaderManager.h"
#include "ModelsManager.h"
#include "Core/Init/IListener.h"
#include <time.h>

namespace Managers
{
	class SceneManager : public Core::IListener
	{
	public:
		SceneManager();
		~SceneManager();

		virtual void NotifyBeginFrame();
		virtual void NotifyDisplayFrame();
		virtual void NotifyEndFrame();
		virtual void NotifyReshape(int width, int height, int previousWidth, int previousHeight);

		void SetModelsManager(ModelsManager*& modelsManager);

	private:
		Managers::ModelsManager*	m_modelsManager;

		glm::mat4					m_projectionMatrix;
		glm::mat4					m_viewMatrix;
	};
}

#endif
