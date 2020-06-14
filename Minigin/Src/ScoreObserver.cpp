#include "MiniginPCH.h"
#include "ScoreObserver.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "TextComponent.h"

int dae::ScoreObserver::m_AmountOfPlayers = 0;

dae::ScoreObserver::ScoreObserver(Subject* entityCounter,const glm::vec2& position)
	:m_EntityCounter{ entityCounter }, m_PlayerID{ ++m_AmountOfPlayers }, m_ScorePlayer{std::make_shared<GameObject>("player_score", true)},
	m_HealthPlayer{std::make_shared<GameObject>("player_health", true)}
{
	entityCounter->Register(this);

	auto font = ResourceManager::GetInstance().LoadFont("/RESIZE/Lingua.otf", m_FontSize);

	m_ScorePlayer->AddComponent<Transform>(static_cast<int>(position.x), static_cast<int>(position.y), 0, 0, 1, 1, 1);
	if(m_PlayerID == 1)
		m_ScorePlayer->AddComponent<TextComponent>("score player 1: 0", font);
	else if(m_PlayerID == 2)
		m_ScorePlayer->AddComponent<TextComponent>("score player 2: 0", font);

	SceneManager::GetInstance().GetActiveScene()->Add(m_ScorePlayer);

	m_HealthPlayer->AddComponent<Transform>(static_cast<int>(position.x), static_cast<int>(position.y + m_Offset), 0, 0, 1, 1, 1);
	if (m_PlayerID == 1)
		m_HealthPlayer->AddComponent<TextComponent>("Health Player 1: 4", font);
	else if(m_PlayerID == 2)
		m_HealthPlayer->AddComponent<TextComponent>("Health Player 2: 4", font);


	SceneManager::GetInstance().GetActiveScene()->Add(m_HealthPlayer);

}

void dae::ScoreObserver::Update(int enemiesAlive, int scorePlayer1, int scorePlayer2, int healthPlayer1, int healthPlayer2)
{
	UNREFERENCED_PARAMETER(enemiesAlive);
	if (m_PlayerID == 1)
	{
		m_ScorePlayer->GetComponent<TextComponent>()->SetText("score player 1: " + std::to_string(scorePlayer1));
		m_HealthPlayer->GetComponent<TextComponent>()->SetText("score player 1: " + std::to_string(healthPlayer1));

	}
	else if (m_PlayerID == 2)
	{
		m_ScorePlayer->GetComponent<TextComponent>()->SetText("score player 2: " + std::to_string(scorePlayer2));
		m_HealthPlayer->GetComponent<TextComponent>()->SetText("score player 2: " + std::to_string(healthPlayer2));


	}
}

void dae::ScoreObserver::InitializeInNewScene()
{
	SceneManager::GetInstance().GetActiveScene()->Add(m_ScorePlayer);
	SceneManager::GetInstance().GetActiveScene()->Add(m_HealthPlayer);
}
