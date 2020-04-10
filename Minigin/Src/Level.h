#pragma once
#include <string>
namespace dae
{
	class Scene;
	class Level
	{
	private:
		std::string m_TextureId;
		int m_Scale;
		int m_TileSize;
		Scene& m_Scene;
	public:
		Level(const std::string& textureId, int scale, int tileSize, Scene& scene);
		~Level() = default;
		void LoadMap(const std::string& filePath, int mapSizeX, int mapSizeY);
		void AddTile(int sourceX, int sourceY, int x, int y);
	};
}

