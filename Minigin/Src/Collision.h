#pragma once
#include <SDL_Rect.h>
namespace dae
{
	//for every object that has a rigidbody + collider component on it you want to just give it the RIGIDBODY_NONE_COLLISION

	class GameObject;
	enum class CollisionType
	{
		NO_COLLISION,
		PLAYER_ENEMY_COLLISION,
		PLAYER_PROJECTILE_COLLISION,
		ENEMY_PROJECTILE_COLLISION,
		PLAYER_TILE_COLLISION,
		ENEMY_TILE_COLLISION,
		PLAYER_NONE_COLLISION,
		RIGID_NONE_COLLISION,
		ITEM_TILE_COLLISION,
		AI_FLOOR_TILE_COLLISION,
		AI_PLATFORM_TILE_COLLISION,
		AI_FLOOR_NONE_COLLISION,
		RIGID_TILE_COLLISION,
		RIGID_HORIZONTAL_SOLID_TILE_COLLISION,
		RIGID_VERTICAL_SOLID_TILE_COLLISION,
		AI_FLOOR_VERTICAL_SOLID_TILE_COLLISION,
		ENEMY_ENEMY_COLLISION
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

