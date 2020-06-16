#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Update(float deltaTime)
{
	if (m_Scenes.size() != 0)
		m_Scenes[m_ActiveSceneId]->Update(deltaTime);
}

void dae::SceneManager::Render()
{
	if(m_Scenes.size() != 0)
		m_Scenes[m_ActiveSceneId]->Render();
}

void dae::SceneManager::SetActiveScene(int id)
{
	m_ActiveSceneId = id;

	//when it switches over to a new scene we have to add the UI back which are the Observers for the score
	SceneManager::GetInstance().GetEntityCounter()->InitializeObserversInNewScene();
	//when it switches to the next level change the enemiesalive back to their proper number
	if (id == 1)
	{
		SceneManager::GetInstance().GetEntityCounter()->SetEnemiesAlive(3);
	}
	else if (id == 2)
	{
		SceneManager::GetInstance().GetEntityCounter()->SetEnemiesAlive(4);
	}
	else if (id == 3)
	{
		SceneManager::GetInstance().GetEntityCounter()->SetEnemiesAlive(2);
	}
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);
	return *scene;
}

void dae::SceneManager::AddGameObjectToAllScenes(const std::shared_ptr<GameObject>& gameObject)
{
	for (auto& scene : m_Scenes)
	{
		scene->Add(gameObject);
	}
}
