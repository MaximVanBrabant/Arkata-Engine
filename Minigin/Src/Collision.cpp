#include "MiniginPCH.h"
#include "Collision.h"
bool dae::Collision::CheckRectangleCollision(const SDL_Rect& rectangleA, const SDL_Rect& rectangleB)
{
	return(rectangleA.x + rectangleA.w >= rectangleB.x &&
		rectangleB.x + rectangleB.w >= rectangleA.x &&
		rectangleA.y + rectangleA.h >= rectangleB.y &&
		rectangleB.y + rectangleB.h >= rectangleA.y);
}

//the reason we need this function is because we optimised the double for loop in the collisionfunction but because it ignores twins of collisions we need to check both expectedTags on both objectTags
bool dae::Collision::CheckCollisionTypeWithTags(const std::string& firstTag, const std::string& secondTag, const std::string& firstExpectedTag, const std::string& secondExpectedTag)
{
	if (firstTag.compare(firstExpectedTag) == 0 && secondTag.compare(secondExpectedTag) == 0)
	{
		return true;
	}
	else if (firstTag.compare(secondExpectedTag) == 0 && secondTag.compare(firstExpectedTag) == 0)
	{
		return true;
	}

	return false;
}
