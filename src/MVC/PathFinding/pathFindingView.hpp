#ifndef __PATHFINDING_VIEW_HPP__
#define __PATHFINDING_VIEW_HPP__

#include "../view.hpp"
#include "pathFindingModel.hpp"

class PathFindingView
	: public View
{
public:
	PathFindingView(sf::RenderWindow& window);

	void renderSceneToTexture() override;
	void updateImGuiUIOptionsWindow() override;

private:
};

#endif