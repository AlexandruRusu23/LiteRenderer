#include "ModelsManager.h"

using namespace LiteRenderer;
using namespace Managers;

ModelsManager::ModelsManager()
{

}

ModelsManager::~ModelsManager()
{
	m_gameModelList.clear();
}

void ModelsManager::Update()
{
	for (auto& model : m_gameModelList)
	{
		model.second->Update();
	}
}

void ModelsManager::Draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix)
{
	for (auto& model : m_gameModelList)
	{
		model.second->Draw(projection_matrix, view_matrix);
	}
}

const Rendering::IGameObject& ModelsManager::GetModel(const std::string& gameModelName) const
{
	return *m_gameModelList.at(gameModelName);
}

void ModelsManager::SetModel(const std::string& gameObjectName, std::unique_ptr<Rendering::IGameObject> gameObject)
{
	m_gameModelList[gameObjectName.c_str()] = std::move(gameObject);
}

void ModelsManager::DeleteModel(const std::string& gameModelName)
{
	m_gameModelList.erase(gameModelName);
}

