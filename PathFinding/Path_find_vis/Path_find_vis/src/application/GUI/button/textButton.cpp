#include "pch.h"
#include "textButton.h"

namespace PFAV::GUI
{
	const std::string TextButton::textName = "mainText";
	const sf::Vector2i TextButton::defaultPadding = {16, 9};

#pragma region Constructors
	TextButton::TextButton()
		: Button("textButton", {0, 0, 0, 0})
	{
		createMainText("default text");
	}

	TextButton::TextButton(const std::string& name, const sf::IntRect& boundingRect, const std::string& buttonText)
		: Button(name, boundingRect)
	{
		createMainText(buttonText);
	}

	TextButton::TextButton(const std::string& name, const sf::IntRect& boundingRect, const std::string& buttonText, const Resources::Font& font)
		: Button(name, boundingRect)
	{
		createMainText(buttonText);
	}

	TextButton::TextButton(const TextButton& other)
		: Button(other)
	{}

	TextButton::TextButton(TextButton&& other) noexcept
		: Button(std::move(other))
	{}
#pragma endregion

	void TextButton::drawElement(sf::RenderWindow& window) const
	{
		window.draw(buttonBackground);
	}

	void TextButton::createMainText(const std::string& buttonText)
	{
		auto mainTextPosition = sf::Vector2i(this->boundingRect.left + this->defaultPadding.x,
											 this->boundingRect.top + this->defaultPadding.y * 0.5f);
		auto mainText = Text("mainText", sf::IntRect(mainTextPosition, {0, 0}), buttonText);
		this->children.push_back(std::make_unique<Text>(mainText));

		auto mainTextBoundingRect = mainText.getBoundingRect();
		auto currentBoundingRect = this->boundingRect;

		this->boundingRect = sf::IntRect(currentBoundingRect.left,
										 currentBoundingRect.top,
										 mainTextBoundingRect.width + 2 * this->defaultPadding.x,
										 mainTextBoundingRect.height + 2 * this->defaultPadding.y);
		this->buttonBackground.setSize(sf::Vector2f(this->boundingRect.width, this->boundingRect.height));
	}
}
