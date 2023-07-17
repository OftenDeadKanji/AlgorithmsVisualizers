#ifndef __MENU_VIEW_HPP__
#define __MENU_VIEW_HPP__

#include "../../Base/View/view.hpp"
#include "../Model/menuModel.hpp"

class MenuView
	: public View
{
public:
	MenuView(const MenuModel& model, sf::RenderWindow& window);

	void renderSceneToTexture() override;
	void updateImGuiUIOptionsWindow() override;

	void setSortingButtonClickCallback(std::function<void()> callback);
	void setPathFindingButtonClickCallback(std::function<void()> callback);
private:
	const MenuModel& m_model = static_cast<const MenuModel&>(m_baseModel);

	std::function<void()> m_callback_onSortingButtonClick;
	std::function<void()> m_callback_onPathFindingButtonClick;
};

#endif