#pragma once
#include "Singleton.h"
#include <map>
namespace dae
{
	class Texture2D;
	class Font;
	class ResourceManager final : public Singleton<ResourceManager>
	{
	public:
		void Init(const std::string& data);
		void AddTexture(const std::string& textureId, const std::string& filename);
		const std::shared_ptr<Texture2D>& GetTexture(const std::string& textureId) const;
		std::shared_ptr<Font> LoadFont(const std::string& file, unsigned int size) const;
	private:
		friend class Singleton<ResourceManager>;
		ResourceManager() = default;
		std::map<std::string, std::shared_ptr<Texture2D>> m_pTextures;
		std::string m_DataPath;
	};
}
