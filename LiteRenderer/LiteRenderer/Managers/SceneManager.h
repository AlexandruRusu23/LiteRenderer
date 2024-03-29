#ifndef MANAGERS_SCENEMANAGER_H
#define MANAGERS_SCENEMANAGER_H

#include "ShaderManager.h"
#include "ModelsManager.h"
#include "Core/Init/IListener.h"
#include "Rendering/ICamera.h"

namespace LiteRenderer
{
	namespace Managers
	{
		class SceneManager : public Core::IListener
		{
		public:
			SceneManager();
			~SceneManager();

			// drawing
			virtual void NotifyBeginFrame();
			virtual void NotifyDisplayFrame();
			virtual void NotifyEndFrame();
			virtual void NotifyReshape(int width, int height, int previousWidth, int previousHeight);

			// input
			virtual void NotifyKeyboardPressed(unsigned char key, int x, int y);
			virtual void NotifyKeyboardReleased(unsigned char key, int x, int y);
			virtual void NotifySpecialKeyboardPressed(int key, int x, int y);
			virtual void NotifySpecialKeyboardReleased(int key, int x, int y);
			virtual void NotifyMouse(int button, int state, int x, int y);
			virtual void NotifyMouseWheel(int button, int state, int x, int y);
			virtual void NotifyMouseMotion(int x, int y);
			virtual void NotifyMousePassiveMotion(int x, int y);

			void SetModelsManager(std::shared_ptr<ModelsManager>& modelsManager);
			void SetCamera(std::shared_ptr<Rendering::ICamera>& camera);

		private:
			std::shared_ptr<Managers::ModelsManager> m_modelsManager;
			std::shared_ptr<Rendering::ICamera> m_camera;

			glm::mat4					m_projectionMatrix;
			glm::mat4					m_viewMatrix;
		};
	}
}

#endif // !MANAGERS_SCENEMANAGER_H

