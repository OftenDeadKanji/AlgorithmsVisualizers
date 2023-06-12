#ifndef __VIEW_HPP__
#define __VIEW_HPP__
#include "SFML/Graphics.hpp"
#include <functional>

class View
{
public:
	View(sf::RenderWindow& window);
	virtual ~View() = default;

	void checkEventsAndRender(float deltaTime);

	void setWindowCloseCallback(std::function<void()>);
protected:
	void checkSFMLEvents();
	void updateImGuiUI(float deltaTime);
	void render();
	virtual void renderSceneToTexture() = 0;
	virtual void updateImGuiUIOptionsWindow() = 0;
	void display();

	sf::RenderWindow& m_window;
	sf::RenderTexture m_renderTexture;
	bool m_resizeTexture = false;
	sf::Vector2u m_newTextureSize;

	//Callbacks
	std::function<void()> m_callback_onWindowClose;
};

#endif