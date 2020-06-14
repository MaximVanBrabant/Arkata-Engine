#pragma once
#include "Singleton.h"
#include "EntityCounter.h"
namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);

		void Update(float deltaTime);
		void Render();
		void SetActiveScene(int id);
		const std::shared_ptr<Scene>& GetActiveScene() const { return m_Scenes[m_ActiveSceneId]; }
		int GetActiveSceneId()const { return m_ActiveSceneId; }

		void AddGameObjectToAllScenes(const std::shared_ptr<GameObject>& gameObject);

		EntityCounter* GetEntityCounter() { return &m_EntityCounter; }
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_Scenes;
		int m_ActiveSceneId = 0;



		// make this part of the scenemanager
		EntityCounter m_EntityCounter;

	};
}
