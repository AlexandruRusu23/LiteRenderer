#ifndef MANAGERS_MODELSMANAGER_H
#define MANAGERS_MODELSMANAGER_H

#include <map>
#include <memory>

#include "Rendering/IGameObject.h"

namespace LiteRenderer
{
	namespace Managers
	{
		class ModelsManager
		{
		public:
			ModelsManager();
			~ModelsManager();

			void Update();
			void Draw(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix);

			const Rendering::IGameObject& GetModel(const std::string& gameModelName) const;
			void SetModel(const std::string& gameObjectName, std::unique_ptr<Rendering::IGameObject> gameObject);
			void DeleteModel(const std::string& gameModelName);

		private:
			std::map<std::string, std::unique_ptr<Rendering::IGameObject>> m_gameModelList;
		};
	}
}

#endif // !MANAGERS_MODELSMANAGER_H

