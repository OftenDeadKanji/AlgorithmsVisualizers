#include "menuController.hpp"

MenuController::MenuController(MenuModel& model, MenuView& view)
	: Controller(model, view, ApplicationState::Menu)
{
	view.setSortingButtonClickCallback([&]() {
		m_nextState = ApplicationState::Sorting;
		});
}
