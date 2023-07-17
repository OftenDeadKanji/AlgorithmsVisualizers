#ifndef __MENU_CONTROLLER_HPP__
#define __MENU_CONTROLLER_HPP__

#include "../../Base/Controller/controller.hpp"
#include "../Model/menuModel.hpp"
#include "../View/menuView.hpp"

class MenuController
	: public Controller
{
public:
	MenuController(MenuModel& model, MenuView& view);

private:
	MenuModel& m_model = static_cast<MenuModel&>(m_baseModel);
	MenuView& m_view = static_cast<MenuView&>(m_baseView);
};

#endif