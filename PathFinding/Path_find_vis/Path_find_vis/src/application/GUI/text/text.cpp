#include "pch.h"
#include "text.h"

namespace PFAV
{
	namespace GUI
	{
		const sf::Color Text::defaultColor = sf::Color::Black;

		Text::Text()
			:GUIelement("text", {0, 0, 0, 0}), sf::Text("default Text", Resources::ResourceManager::getInstance()->getDefaultFont(), 50), color(Text::defaultColor)
		{
			this->resize();

			sf::Text::setPosition(boundingRect.left, boundingRect.top);
			sf::Text::setFillColor(sf::Color::Black);
		}

		Text::Text(const std::string& name, const sf::IntRect& boundingRect, const std::string& text, unsigned int characterSize)
			: GUIelement(name, boundingRect), sf::Text(text, Resources::ResourceManager::getInstance()->getDefaultFont(), characterSize),
			color(defaultColor)
		{
			this->resize();

			sf::Text::setPosition(boundingRect.left, boundingRect.top);
			sf::Text::setFillColor(sf::Color::Black);
		}

		Text::Text(const std::string& name, const sf::IntRect& boundingRect, const std::string& text, const Resources::Font& font, unsigned int characterSize)
			: GUIelement(name, boundingRect), sf::Text(text, font, characterSize), color(defaultColor)
		{
			this->resize();

			sf::Text::setPosition(boundingRect.left, boundingRect.top);
			sf::Text::setFillColor(sf::Color::Black);
		}

		Text::Text(const Text& other)
			: GUIelement(other), sf::Text(other)
		{}

		Text::Text(Text&& other) noexcept
			: GUIelement(other), sf::Text(other)
		{}

		void Text::resize()
		{
			auto textBounds = sf::Text::getGlobalBounds();
			auto currentBoundingRect = this->boundingRect;

			this->boundingRect = sf::IntRect(currentBoundingRect.left,
											   currentBoundingRect.top, 
											   textBounds.left + textBounds.width, 
											   textBounds.top + textBounds.height);
		}

		std::string Text::getText() const
		{
			return this->getString();
		}

		void Text::setText(const std::string& text)
		{
			setString(text);
		}

		const sf::Color& Text::getDefaultColor()
		{
			return Text::defaultColor;
		}

		const sf::Color& Text::getCurrentColor() const
		{
			return this->color;
		}

		void Text::setColor(const sf::Color& color)
		{
			this->color = color;
		}

		void Text::drawElement(sf::RenderWindow& window) const
		{
			window.draw(*this);
		}
	}
}