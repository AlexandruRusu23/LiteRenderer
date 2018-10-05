#ifndef MANAGERS_TEXTMANAGER_H
#define MANAGERS_TEXTMANAGER_H

#include <map>

#include "ModelsManager.h"
#include "Rendering/IGameObject.h"

namespace LiteRenderer
{
	namespace Managers
	{
		class TextManager
		{
		public:
			TextManager();
			~TextManager();

			void SetModelsManager(ModelsManager*& modelsManager);

		private:
			Managers::ModelsManager* m_modelsManager = nullptr;

			std::map<std::string, Rendering::IGameObject*> m_textModelList;
		};
	}
}

#endif // !MANAGERS_TEXTMANAGER_H

