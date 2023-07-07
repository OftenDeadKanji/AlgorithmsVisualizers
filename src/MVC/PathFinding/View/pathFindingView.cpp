#include "pathFindingView.hpp"
#include <ImGUI/imgui.h>

PathFindingView::PathFindingView(const PathFindingModel& model, sf::RenderWindow& window)
	: View(model, window)
{
}

void PathFindingView::renderSceneToTexture()
{
}

void PathFindingView::updateImGuiUIOptionsWindow()
{
	m_algorithmSelector.updateAndDisplaySelector();
	m_boardSizeSelector.updateAndDisplaySelector();
}

void PathFindingView::setAlgorithmSelectCallback(std::function<void(PathFindingAlgorithm)> callback)
{
	m_algorithmSelector.setAlgorithmComboListSelectCallback(callback);
}

void PathFindingView::setBoardSizeChangeCallback(std::function<void(std::pair<int, int>)> callback)
{
	m_boardSizeSelector.setBoardSizeChangeCallback(callback);
}
