#pragma once
//#include "Transform.h"
#include "Texture2D.h"

namespace dae
{
	class SpriteComponent : public Component
	{
	public:
		SpriteComponent() = default;
		void Render() const override;
		void Update(float deltaTime) override;
		int AddTexture(const std::string& filename);
		std::shared_ptr<Texture2D> GetTexture(int id) const;
		//void SetPositionTexture(int id, float x, float y);
	private:
		std::vector<std::shared_ptr<dae::Texture2D>> m_pTextures{};
	};
}

