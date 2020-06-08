#include "MiniginPCH.h"
#include <SDL.h>
#include "EnemySM.h"
#include "EnemyState.h"
#include "SeekEnemyState.h"
#include "JumpEnemyState.h"
#include "AttackEnemyState.h"
#include "BubbleEnemyState.h"
#include "ColliderComponent.h"
#include "Renderer.h"

dae::EnemySM::EnemySM(const std::shared_ptr<GameObject>& pTarget, EnemyType enemyType)
	:m_Seek{ std::make_shared<SeekEnemyState>(this) }, m_Jump{ std::make_shared<JumpEnemyState>(this) }, m_Attack{std::make_shared<AttackEnemyState>(this)},
	m_pTarget{ pTarget }, m_pLeftFloorCollider{ new ColliderComponent("AI_FLOOR") }, m_pLeftPlatformCollider{ new ColliderComponent("AI_PLATFORM") }
	, m_pRightFloorCollider{ new ColliderComponent("AI_FLOOR") }, m_pRightPlatformCollider{ new ColliderComponent("AI_PLATFORM") }, m_EnemyType{ enemyType }
	, m_JumpHeight{}, m_Bubble{std::make_shared<BubbleEnemyState>(this)}
{
}

dae::EnemySM::~EnemySM()
{
	delete m_pLeftFloorCollider;
	delete m_pLeftPlatformCollider;
	delete m_pRightFloorCollider;
	delete m_pRightPlatformCollider;
}

void dae::EnemySM::SwitchState(const std::shared_ptr<EnemyState>& newState)
{
	if (m_CurrentEnemyState != nullptr)
	{
		m_CurrentEnemyState->Exit();
	}

	m_CurrentEnemyState = newState;
	m_CurrentEnemyState->Entry();
}

void dae::EnemySM::Initialize()
{
	m_pLeftFloorCollider->m_Owner = this->m_Owner;
	m_pLeftPlatformCollider->m_Owner = this->m_Owner;
	m_pRightFloorCollider->m_Owner = this->m_Owner;
	m_pRightPlatformCollider->m_Owner = this->m_Owner;

	m_pLeftFloorCollider->Initialize();
	m_pLeftPlatformCollider->Initialize();
	m_pRightFloorCollider->Initialize();
	m_pRightPlatformCollider->Initialize();

	m_pRightFloorCollider->SetOffset(m_Owner->GetComponent<Transform>()->GetWidth(), m_Owner->GetComponent<Transform>()->GetHeight());
	m_pLeftFloorCollider->SetOffset(-m_Owner->GetComponent<Transform>()->GetWidth(),m_Owner->GetComponent<Transform>()->GetHeight());

	m_pLeftPlatformCollider->SetOffset(-30, -80);
	m_pRightPlatformCollider->SetOffset(30, -80);


	m_Seek->Initialize();
	m_Jump->Initialize();
	m_Attack->Initialize();
	m_Bubble->Initialize();
	SwitchState(m_Seek);
}

void dae::EnemySM::Update(float deltaTime)
{
	m_pLeftFloorCollider->Update(deltaTime);
	m_pLeftPlatformCollider->Update(deltaTime);
	m_pRightFloorCollider->Update(deltaTime);
	m_pRightPlatformCollider->Update(deltaTime);
	m_CurrentEnemyState->Update(deltaTime);
}

void dae::EnemySM::JumpIntoAir()
{
	m_CurrentEnemyState->JumpIntoAir();
}

void dae::EnemySM::TrapInBell()
{
	m_CurrentEnemyState->TrapInBell();
}

void dae::EnemySM::SetLeftFloorCollider(bool enable)
{
	m_pLeftFloorCollider->SetEnabled(enable);
}

void dae::EnemySM::SetRightFloorCollider(bool enable)
{
	m_pRightFloorCollider->SetEnabled(enable);
}

void dae::EnemySM::Render() const
{
	SDL_SetRenderDrawColor(dae::Renderer::GetInstance().GetSDLRenderer(), 255, 255, 255, 255);
	if (m_pLeftFloorCollider->GetEnabled())
	{
		SDL_RenderDrawRect(dae::Renderer::GetInstance().GetSDLRenderer(), &m_pLeftFloorCollider->GetCollider());
	}
	if(m_pLeftPlatformCollider->GetEnabled())
		SDL_RenderDrawRect(dae::Renderer::GetInstance().GetSDLRenderer(), &m_pLeftPlatformCollider->GetCollider());
	if(m_pRightFloorCollider->GetEnabled())
		SDL_RenderDrawRect(dae::Renderer::GetInstance().GetSDLRenderer(), &m_pRightFloorCollider->GetCollider());
	if (m_pRightPlatformCollider->GetEnabled())
	{
		SDL_RenderDrawRect(dae::Renderer::GetInstance().GetSDLRenderer(), &m_pRightPlatformCollider->GetCollider());

	}

}
