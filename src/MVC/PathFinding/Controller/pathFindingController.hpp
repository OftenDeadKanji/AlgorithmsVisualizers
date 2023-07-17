#ifndef __PATHFINDING_CONTROLLER_HPP__
#define __PATHFINDING_CONTROLLER_HPP__

#include "../../Base/Controller/controller.hpp"
#include "../Model/pathFindingModel.hpp"
#include "../View/pathFindingView.hpp"

class PathFindingController
	: public Controller
{
public:
	PathFindingController(PathFindingModel& model, PathFindingView& view);

private:
	PathFindingModel& m_model = static_cast<PathFindingModel&>(m_baseModel);
	PathFindingView& m_view = static_cast<PathFindingView&>(m_baseView);
};

#endif