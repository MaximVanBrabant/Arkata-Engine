#pragma once
#include "Component.h"
#include "ColliderComponent.h"

namespace dae
{
	class EnemyState;
	class ColliderComponent;
	class EnemySM : public Component
	{
	public:
		EnemySM(const std::shared_ptr<GameObject>& pTarget);
		~EnemySM();
		void SwitchState(const std::shared_ptr<EnemyState>& newState);
		void Initialize() override;
		void Render() const override;

		void Update(float deltaTime) override;
		void JumpIntoAir();

		const std::shared_ptr<EnemyState>& GetSeekState() const { return m_Seek; }
		const std::shared_ptr<EnemyState>& GetJumpState() const { return m_Jump; }
		const std::shared_ptr<EnemyState>& GetAttackState() const { return m_Attack; }

		const std::weak_ptr<GameObject>& GetTarget() const { return m_pTarget; }
		float GetToCloseDistance () const { return m_ToCloseDistance; }

		ColliderComponent* GetLeftFloorCollider() const { return m_pLeftFloorCollider; }
		ColliderComponent* GetRightFloorCollider() const { return m_pRightFloorCollider; }
		ColliderComponent* GetLeftPlatformCollider() const { return m_pLeftPlatformCollider; }
		ColliderComponent* GetRightPlatformCollider() const { return m_pRightPlatformCollider; }

		void SetLeftFloorCollider(bool enable);
		void SetRightFloorCollider(bool enable);
		void SetLeftPlatformCollider(bool enable) { m_pLeftPlatformCollider->SetEnabled(enable); }
		void SetRightPlatformCollider(bool enable) { m_pRightPlatformCollider->SetEnabled(enable); }

		float GetJumpHeight() const { return m_JumpHeight; }
		void SetJumpHeight(float jumpHeight) { m_JumpHeight = jumpHeight; }

		float GetVerticalJumpHeight() const { return m_VerticalJumpHeight; }
		float GetHorizontalJumpHeight() const { return m_HorizontalJumpHeight; }

	private:
		std::shared_ptr<EnemyState> m_Seek;
		std::shared_ptr<EnemyState> m_Jump;
		std::shared_ptr<EnemyState> m_Attack;

		std::shared_ptr<EnemyState> m_CurrentEnemyState;

		//still needs a specific kind of enemy

		std::weak_ptr<GameObject> m_pTarget;
		const float m_ToCloseDistance = 150.f;

		//add colliders
		ColliderComponent* m_pLeftFloorCollider = nullptr;
		ColliderComponent* m_pRightFloorCollider = nullptr;

		ColliderComponent* m_pLeftPlatformCollider = nullptr;
		ColliderComponent* m_pRightPlatformCollider = nullptr;

		//jump para
		const float m_HorizontalJumpHeight = -175.f;
		const float m_VerticalJumpHeight = -250.f;
		float m_JumpHeight;
	};
}

