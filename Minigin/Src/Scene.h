#pragma once
#include "SceneManager.h"

namespace dae
{
	struct CollisionInfo;
	class GameObject;
	class Scene
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void Add(const std::shared_ptr<GameObject>& object);

		void Update(float deltaTime);
		void Render() const;

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;
		const std::vector <std::shared_ptr<GameObject>>& GetGameObjects() const { return m_Objects; }


		int GetId() const;
		void ListAllEntities() const;

	private: 
		explicit Scene(const std::string& name);

		std::string m_Name;
		unsigned int m_Id;
		std::vector < std::shared_ptr<GameObject>> m_Objects{};
		std::vector<int> m_NonActiveIndices;

		//static
		static unsigned int m_IdCounter; 

	};

}
