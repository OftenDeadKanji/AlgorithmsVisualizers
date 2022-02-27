#pragma once
#include "../GUIelement.h"
#include "../../resources/resourceManager.h"

namespace PFAV
{
	namespace GUI
	{
		class Text
			: public sf::Text, public GUIelement
		{
		public:
			Text();
			Text(const std::string& name, const sf::IntRect& boundingRect, const std::string& text, unsigned int characterSize = 30);
			Text(const std::string& name, const sf::IntRect& boundingRect, const std::string& text, const Resources::Font& font, unsigned int characterSize = 30);

			Text(const Text&);
			Text(Text&&) noexcept;

			void resize();

			std::string getText() const;
			void setText(const std::string& text);

			static const sf::Color& getDefaultColor();
			const sf::Color& getCurrentColor() const;
			void setColor(const sf::Color&);

			virtual void update(const sf::RenderWindow& window, const sf::Mouse&) override
			{};

			void drawElement(sf::RenderWindow& window) const override;
		private:
			static const sf::Color defaultColor;
			sf::Color color;
		};

	}
}