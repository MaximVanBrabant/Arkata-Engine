#include "MiniginPCH.h"
#include <fstream>
#include "GameObject.h"
#include "Level.h"
#include "TileComponent.h"
#include "Scene.h"
#include "ColliderComponent.h"
#include "Constants.h"

dae::Level::Level(const std::string& textureId, int scale, int tileSize, Scene& scene)
	:m_TextureId{textureId}, m_Scale{scale}, m_TileSize{tileSize}, m_Scene{scene}
{
}

void dae::Level::LoadMap(const std::string& filePath, int mapSizeX, int mapSizeY)
{
	//parse the .map file -> 20cols/15rows
	std::fstream mapFile;

	mapFile.open(filePath);
	if (!mapFile)
	{
		std::cout << "file not correctly opened" << std::endl;
		return;
	}

	for (int y = 0; y < mapSizeY; y++)
	{
		for (int x = 0; x < mapSizeX; ++x)
		{
			char input;
			mapFile.get(input);
			int srcRectY = std::atoi(&input) * m_TileSize;
			mapFile.get(input);
			int srcRectX = std::atoi(&input) * m_TileSize;
			//when you have 00 as indices dont make a tile its just a black hole
			if (srcRectX == 0 && srcRectY == 0)
			{
				mapFile.ignore();
				continue;
			}
			AddTile(srcRectX, srcRectY, x * m_Scale * m_TileSize, y * m_Scale * m_TileSize);
			mapFile.ignore();

		}

	}
	mapFile.close();
}

void dae::Level::AddTile(int sourceX, int sourceY, int x, int y)
{
	//add transform
	std::shared_ptr<GameObject> tile{ std::make_shared<GameObject>("tile", true) };
	tile->AddComponent<Transform>(x, y, 0,0,m_TileSize, m_TileSize, m_Scale);
	tile->AddComponent<TileComponent>(sourceX, sourceY, x , y,m_TileSize, m_Scale, m_TextureId);
	if (sourceX == 1 * m_TileSize)
		tile->AddComponent<ColliderComponent>("TILE");
	else if (sourceX == 2 * m_TileSize)
		tile->AddComponent<ColliderComponent>("HORIZONTAL_SOLID_TILE");
	else if (sourceX == 3 * m_TileSize)
		tile->AddComponent<ColliderComponent>("VERTICAL_SOLID_TILE");
	m_Scene.Add(tile);
}
