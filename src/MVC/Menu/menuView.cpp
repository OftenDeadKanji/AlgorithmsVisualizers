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
}

void MenuView::setSortingButtonClickCallback(std::function<void()> callback)
{
	m_callback_onSortingButtonClick = std::move(callback);
}
