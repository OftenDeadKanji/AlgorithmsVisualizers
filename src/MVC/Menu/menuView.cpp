#include "menuView.hpp"
#include <ImGUI/imgui.h>

MenuView::MenuView(sf::RenderWindow& window)
	: View(window)
{
}

void MenuView::renderSceneToTexture()
{
}

void MenuView::updateImGuiUIOptionsWindow()
{
	if (ImGui::Button("Sorting"))
	{
		if (m_callback_onSortingButtonClick)
		{
			m_callback_onSortingButtonClick();
		}
	}
	if (ImGui::Button("Path Finding"))
	{
		if (m_callback_onPathFindingButtonClick)
		{
			m_callback_onPathFindingButtonClick();
		}
	}
}

void MenuView::setSortingButtonClickCallback(std::function<void()> callback)
{
	m_callback_onSortingButtonClick = std::move(callback);
}

void MenuView::setPathFindingButtonClickCallback(std::function<void()> callback)
{
	m_callback_onPathFindingButtonClick = std::move(callback);
}
