#include "TextManager.h"

using namespace LiteRenderer;
using namespace Managers;

TextManager::TextManager()
{

}

TextManager::~TextManager()
{
	for (auto model : m_textModelList)
	{
		delete model.second;
		model.second = nullptr;
	}
	m_textModelList.clear();
}

void TextManager::SetModelsManager(ModelsManager*& modelsManager)
{
	m_modelsManager = modelsManager;
}

