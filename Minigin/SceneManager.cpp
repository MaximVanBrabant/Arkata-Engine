#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Update(float deltaTime)
{
	m_Scenes[m_ActiveSceneId]->Update(deltaTime);
}

void dae::SceneManager::Render()
{
	m_Scenes[m_ActiveSceneId]->Render();
}

void dae::SceneManager::SetActiveScene(int id)
{
	m_ActiveSceneId = id;
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);
	return *scene;
}
