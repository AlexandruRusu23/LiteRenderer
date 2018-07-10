#ifndef MODELS_MANAGER_H
#define MODELS_MANAGER_H

#include <map>

#include "..\Rendering\IGameObject.h"

using namespace Rendering;

namespace Managers
{
	class ModelsManager
	{
	public:
		ModelsManager();
		~ModelsManager();

		void Draw();
		void Draw(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix);
		void Update();

		void DeleteModel(const std::string& gameModelName);
		const IGameObject& GetModel(const std::string& gameModelName) const;
		void SetModel(const std::string& gameObjectName, IGameObject* gameObject);

	private:
		std::map<std::string, IGameObject*> m_gameModelList;
	};
}

#endif
