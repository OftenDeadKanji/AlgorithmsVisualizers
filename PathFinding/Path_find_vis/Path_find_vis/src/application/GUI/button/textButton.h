#pragma once
#include "button.h"
#include "../text/text.h"

namespace PFAV::GUI
{
	class TextButton final :
		public Button
	{
	public:
		TextButton();
		TextButton(const std::string& name, const sf::IntRect& boundingRect, const std::string& buttonText);
		TextButton(const std::string& name, const sf::IntRect& boundingRect, const std::string& buttonText, const Resources::Font& font);
		TextButton(const TextButton&);
		TextButton(TextButton&&) noexcept;

		void drawElement(sf::RenderWindow& window) const override;
	private:
		void createMainText(const std::string& buttonText);

		static const std::string textName;
		static const sf::Vector2i defaultPadding;
	};

}
