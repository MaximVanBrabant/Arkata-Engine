#pragma once
#include "Component.h"
#include "ColliderComponent.h"

namespace dae
{
	enum class EnemyType
	{
		Charge,
		Throw
	};


	class EnemyState;
	class ColliderComponent;
	class EnemySM : public Component
	{
	public:
		EnemySM(const std::shared_ptr<GameObject>& pTarget, EnemyType enemyType);
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
		float GetToCloseMeleeDistance () const { return m_ToCloseMeleeDistance; }
		float GetToCloseRangedDistance() const { return m_ToCloseRangedDistance; }

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

		bool GetInverseMovement() const { return m_InverseMovement; }
		void SetInverseMovement(bool enable) { m_InverseMovement = enable; }

		bool GetHasAttacked() const { return m_HasAttacked; }
		void SetHasAttacked(bool attacked) { m_HasAttacked = attacked; }

		EnemyType GetEnemyType() const { return m_EnemyType; }

	private:
		std::shared_ptr<EnemyState> m_Seek;
		std::shared_ptr<EnemyState> m_Jump;
		std::shared_ptr<EnemyState> m_Attack;

		std::shared_ptr<EnemyState> m_CurrentEnemyState;

		std::weak_ptr<GameObject> m_pTarget;

		const float m_ToCloseMeleeDistance = 150.f;
		const float m_ToCloseRangedDistance = 500.f;

		//add colliders
		ColliderComponent* m_pLeftFloorCollider = nullptr;
		ColliderComponent* m_pRightFloorCollider = nullptr;

		ColliderComponent* m_pLeftPlatformCollider = nullptr;
		ColliderComponent* m_pRightPlatformCollider = nullptr;

		const float m_HorizontalJumpHeight = -175.f;
		const float m_VerticalJumpHeight = -250.f;
		float m_JumpHeight;

		bool m_InverseMovement = false;

		bool m_HasAttacked = false;

		EnemyType m_EnemyType;

	};
}

