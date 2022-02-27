#pragma once
#include "../GUIelement.h"

namespace PFAV::GUI
{
	class Button :
		public GUIelement
	{
	public:
		Button(const std::string& name, const sf::IntRect& boundingRect);
		Button(const Button&);
		Button(Button&&) noexcept;
		~Button() override = default;

		void setOnClickCallback(std::function<void(void)>);

		void update(const sf::RenderWindow& window, const sf::Mouse&) override;

	protected:
		virtual void initWithDefaultAppearance();
			
		std::function<void(void)> onClickCallback;
		double clickTimeCooldown = 1.0;
		std::chrono::time_point<std::chrono::steady_clock> lastClick;
			
		sf::RectangleShape buttonBackground;
			
		sf::Color currentColor;
		//static const sf::Color defaultColor;
		const sf::Color idleColor;
		const sf::Color hoveredColor;
		const sf::Color clickedColor;

	};
}
