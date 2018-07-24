#include "ModelsManager.h"

using namespace LiteRenderer;
using namespace Managers;

ModelsManager::ModelsManager()
{

}

ModelsManager::~ModelsManager()
{
	for (auto model : m_gameModelList)
	{
		delete model.second;
		model.second = nullptr;
	}
	m_gameModelList.clear();
}

void ModelsManager::Update()
{
	for (auto model : m_gameModelList)
	{
		model.second->Update();
	}
}

void ModelsManager::Draw()
{
	for (auto model : m_gameModelList)
	{
		model.second->Draw();
	}
}

void ModelsManager::Draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix)
{
	for (auto model : m_gameModelList)
	{
		model.second->Draw(projection_matrix, view_matrix);
	}
}

const Rendering::IGameObject& ModelsManager::GetModel(const std::string& gameModelName) const
{
	return (*m_gameModelList.at(gameModelName));
}

void ModelsManager::SetModel(const std::string& gameObjectName, Rendering::IGameObject* gameObject)
{
	m_gameModelList[gameObjectName.c_str()] = gameObject;
}

void ModelsManager::DeleteModel(const std::string& gameModelName)
{
	Rendering::IGameObject* model = m_gameModelList[gameModelName];
	model->Destroy();
	m_gameModelList.erase(gameModelName);
}

