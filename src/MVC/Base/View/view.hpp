#ifndef __VIEW_HPP__
#define __VIEW_HPP__
#include "SFML/Graphics.hpp"
#include <functional>
#include "../Model/model.hpp"

class View
{
public:
	View(const Model& model, sf::RenderWindow& window);
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

	const Model& m_baseModel;

	sf::RenderWindow& m_window;
	sf::RenderTexture m_renderTexture;
	bool m_resizeTexture = false;
	sf::Vector2u m_newTextureSize;

	//Callbacks
	std::function<void()> m_callback_onWindowClose;
};

#endif