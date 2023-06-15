#ifndef __PATHFINDING_VIEW_HPP__
#define __PATHFINDING_VIEW_HPP__

#include "../../Base/View/view.hpp"
#include "../Model/pathFindingModel.hpp"

class PathFindingView
	: public View
{
public:
	PathFindingView(const PathFindingModel& model, sf::RenderWindow& window);

	void renderSceneToTexture() override;
	void updateImGuiUIOptionsWindow() override;

private:
	const PathFindingModel& m_model = static_cast<const PathFindingModel&>(m_baseModel);
};

#endif