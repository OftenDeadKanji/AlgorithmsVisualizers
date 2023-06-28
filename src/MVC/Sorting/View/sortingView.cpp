#include "sortingView.hpp"
#include <ImGUI/imgui.h>
#include "../Model/sortingModel.hpp"

SortingView::SortingView(sf::RenderWindow& window)
	: View(window)
{
	m_algorithmSelector.setAvailableAlgorithms(SortingModel::getAllAvailableSortingAlgorithms());
}

void SortingView::renderSceneToTexture()
{
}

void SortingView::updateImGuiUIOptionsWindow()
{
	m_algorithmSelector.updateAndDisplayComboList();
}

void SortingView::setAlgorithmComboListSelectCallback(std::function<void(SortingAlgorithm)> callback)
{
	m_algorithmSelector.setAlgorithmComboListSelectCallback(callback);
}
