#ifndef __VIEW_HPP__
#define __VIEW_HPP__
#include "SFML/Graphics.hpp"
#include <functional>

class View
{
public:
	View();
	~View();

	void checkEventsAndRender(float deltaTime);

	void setWindowCloseCallback(std::function<void()>);
private:
	void checkSFMLEvents();
	void updateImGuiUI(float deltaTime);
	void renderSceneToTexture();
	void render();

	// RenderWindow and RenderTexture
	static constexpr sf::Vector2u DEFAULT_WINDOW_SIZE { 1600, 900 };
	const sf::String DEFAULT_WINDOW_TITLE { L"Algorithms Visualizer - Mateusz Ch³opek 2023" };
	sf::RenderWindow m_window;

	sf::RenderTexture m_renderTexture;
	bool m_resizeTexture = false;
	sf::Vector2u m_newTextureSize;

	//Callbacks
	std::function<void()> m_callback_onWindowClose;
};

#endif