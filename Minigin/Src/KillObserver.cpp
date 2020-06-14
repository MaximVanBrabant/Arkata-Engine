#include "MiniginPCH.h"
#include "KillObserver.h"
#include "SceneManager.h"
#include "Scene.h"
void dae::KillObserver::Update(int enemiesAlive, int scorePlayer1, int scorePlayer2, int playerHealth1, int playerHealth2)
{
	UNREFERENCED_PARAMETER(scorePlayer1);
	UNREFERENCED_PARAMETER(scorePlayer2);
	UNREFERENCED_PARAMETER(playerHealth1);
	UNREFERENCED_PARAMETER(playerHealth2);
	if (enemiesAlive == 0)
	{
		//go to next level
		SceneManager::GetInstance().SetActiveScene(1 + SceneManager::GetInstance().GetActiveSceneId());
	}
}
