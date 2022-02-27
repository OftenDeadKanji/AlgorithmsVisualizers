#include "pch.h"
#include "button.h"

#include <utility>

namespace PFAV::GUI
{
	Button::Button(const std::string& name, const sf::IntRect& boundingRect)
		: GUIelement(name, boundingRect), idleColor(sf::Color::White), hoveredColor(sf::Color(100, 100, 100)), clickedColor(sf::Color(180, 180, 180))
	{
		this->onClickCallback = [this]()
		{
			std::cout << "\"" << this->name << "\" button has been clicked!" << std::endl;
		};

		initWithDefaultAppearance();

		buttonBackground.setPosition(boundingRect.left, boundingRect.top);
	}

	Button::Button(const Button& other)
		: GUIelement(other),
		onClickCallback(other.onClickCallback),
		clickTimeCooldown(other.clickTimeCooldown), lastClick(other.lastClick),
		buttonBackground(other.buttonBackground),
		currentColor(other.currentColor), idleColor(other.idleColor), hoveredColor(other.hoveredColor), clickedColor(other.clickedColor)
	{

	}

	Button::Button(Button&& other) noexcept
		: GUIelement(std::move(other)),
		onClickCallback(std::move(other.onClickCallback)),
		clickTimeCooldown(other.clickTimeCooldown), lastClick(other.lastClick),
		buttonBackground(std::move(other.buttonBackground)),
		currentColor(other.currentColor), idleColor(other.idleColor), hoveredColor(other.hoveredColor), clickedColor(other.clickedColor)
	{}

	void Button::setOnClickCallback(std::function<void(void)> newCallback)
	{
		this->onClickCallback = std::move(newCallback);
	}

	void Button::update(const sf::RenderWindow& window, const sf::Mouse& mouse)
	{
		if(this->enabled)
		{
			if(this->boundingRect.contains(mouse.getPosition(window)))
			{
				if(mouse.isButtonPressed(sf::Mouse::Button::Left))
				{	// clicked
					this->buttonBackground.setFillColor(this->clickedColor);

					std::chrono::duration<double> duration = std::chrono::steady_clock::now() - this->lastClick;
					if(duration.count() >= this->clickTimeCooldown)
					{
						this->lastClick = std::chrono::steady_clock::now();

						this->onClickCallback();
					}
				}
				else
				{	// just hovered
					this->buttonBackground.setFillColor(this->hoveredColor);
				}

			}
			else
			{	// idle
				this->buttonBackground.setFillColor(this->idleColor);
			}
		}
		else
		{
			this->buttonBackground.setFillColor(this->idleColor);
		}
	}

	void Button::initWithDefaultAppearance()
	{
		buttonBackground.setFillColor(this->idleColor);
		buttonBackground.setOutlineColor(sf::Color::Black);
		buttonBackground.setOutlineThickness(2);
	}
}
