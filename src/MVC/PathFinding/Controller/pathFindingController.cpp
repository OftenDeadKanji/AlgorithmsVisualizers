#include "pathFindingController.hpp"

PathFindingController::PathFindingController(PathFindingModel& model, PathFindingView& view)
	: Controller(model, view, ApplicationState::PathFinding)
{
}
