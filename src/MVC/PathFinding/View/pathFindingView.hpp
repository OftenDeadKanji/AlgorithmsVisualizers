#ifndef __PATHFINDING_VIEW_HPP__
#define __PATHFINDING_VIEW_HPP__

#include "../../Base/View/view.hpp"
#include "../Model/pathFindingModel.hpp"
#include "../../Base/View/algorithmSelector.hpp"
#include "boardSizeSelector.hpp"

class PathFindingView
	: public View
{
public:
	PathFindingView(const PathFindingModel& model, sf::RenderWindow& window);

	void renderSceneToTexture() override;
	void updateImGuiUIOptionsWindow() override;

	void setAlgorithmSelectCallback(std::function<void(PathFindingAlgorithm)> callback);
	void setBoardSizeChangeCallback(std::function<void(std::pair<int, int>)> callback);

private:
	const PathFindingModel& m_model = static_cast<const PathFindingModel&>(m_baseModel);
	AlgorithmSelector<PathFindingAlgorithm> m_algorithmSelector;
	BoardSizeSelector m_boardSizeSelector;
};

#endif