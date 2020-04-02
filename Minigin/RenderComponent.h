#pragma once
#include "Transform.h"
#include "Texture2D.h"
namespace dae
{

	class RenderComponent
	{
	public:
		RenderComponent() = default;
		void Render(dae::Transform transform) const;
		int AddTexture(const std::string& filename);
		std::shared_ptr<Texture2D> GetTexture(int id) const;
		void SetPositionTexture(int id, float x, float y, float z);
	private:
		std::vector<std::shared_ptr<dae::Texture2D>> m_pTextures{};
	};
}

