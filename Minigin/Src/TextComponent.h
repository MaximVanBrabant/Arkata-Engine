#pragma once
#include "Transform.h"

namespace dae
{
	class Font;
	class Texture2D;

	class TextComponent
	{
	public:
		TextComponent(const std::string& text, const std::shared_ptr<Font>& font);

		void Update(float deltaTime);
		void Render() const;
		void SetText(const std::string& text);
		void SetPosition(float x, float y);

	private:
		bool m_NeedsUpdate;
		std::string m_Text;
		std::shared_ptr<Font> m_Font;
		std::shared_ptr<Texture2D> m_Texture;
	};
}

