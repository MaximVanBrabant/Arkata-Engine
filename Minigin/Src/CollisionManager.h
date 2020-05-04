#pragma once
#include "Singleton.h"

namespace dae
{
	struct CollisionInfo;

	class CollisionManager final : public Singleton<CollisionManager>
	{
	public:
		void CollisionUpdate();
	private:
		friend class Singleton<CollisionManager>;
		void CheckGameObjectCollisions();
		void ApplyCollisionEffects(CollisionInfo collisionInfo);
	};
}

