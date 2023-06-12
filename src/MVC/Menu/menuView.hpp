#ifndef __MENU_VIEW_HPP__
#define __MENU_VIEW_HPP__

#include "../view.hpp"
#include "menuModel.hpp"

class MenuView
	: public View
{
public:
	MenuView(sf::RenderWindow& window);

	void renderSceneToTexture() override;
	void updateImGuiUIOptionsWindow() override;

	void setSortingButtonClickCallback(std::function<void()> callback);
private:
	std::function<void()> m_callback_onSortingButtonClick;
};

#endif