#include "ModelsManager.h"

using namespace Managers;
using namespace Rendering;

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

void ModelsManager::DeleteModel(const std::string& gameModelName)
{
	IGameObject* model = m_gameModelList[gameModelName];
	model->Destroy();
	m_gameModelList.erase(gameModelName);
}

const IGameObject& ModelsManager::GetModel(const std::string& gameModelName) const
{
	return (*m_gameModelList.at(gameModelName));
}

void ModelsManager::SetModel(const std::string& gameObjectName, IGameObject* gameObject)
{
	m_gameModelList[gameObjectName.c_str()] = gameObject;
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
