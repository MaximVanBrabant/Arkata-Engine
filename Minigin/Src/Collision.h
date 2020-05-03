#pragma once
#include <SDL_Rect.h>
namespace dae
{
	class GameObject;
	enum class CollisionType
	{
		NO_COLLISION,
		PLAYER_ENEMY_COLLISION,
		PLAYER_PROJECTILE_COLLISION,
		ENEMY_PROJECTILE_COLLISION,
		PLAYER_TILE_COLLISION,
		ENEMY_TILE_COLLISION
	};

	struct CollisionInfo
	{
		CollisionInfo(CollisionType type,const std::shared_ptr<GameObject>& first,const std::shared_ptr<GameObject> second)
			:collisionType{type}, firstGameObject{first}, secondGameObject{second}
		{

		}

		CollisionType collisionType;
		std::shared_ptr<GameObject> firstGameObject;
		std::shared_ptr<GameObject> secondGameObject;
	};

	class Collision
	{
	public:
		static bool CheckRectangleCollision(const SDL_Rect& rectangleA, const SDL_Rect& rectangleB);
		static bool CheckCollisionTypeWithTags(const std::string& firstTag, const std::string& secondTag, const std::string& firstExpectedTag, const std::string& secondExpectedTag);
	private:
	};
}

