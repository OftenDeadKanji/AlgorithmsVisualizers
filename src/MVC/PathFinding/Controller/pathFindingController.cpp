#include "pathFindingController.hpp"

PathFindingController::PathFindingController(PathFindingModel& model, PathFindingView& view)
	: Controller(model, view, ApplicationState::PathFinding)
{
	m_view.setAlgorithmSelectCallback([&](PathFindingAlgorithm algorithm) 
		{
			model.setAlgorithm(algorithm);
		});

	m_view.setBoardSizeChangeCallback([&](std::pair<int, int> size)
		{
			model.setBoardSize(size);
		});
}
