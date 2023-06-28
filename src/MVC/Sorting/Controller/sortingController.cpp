#include "sortingController.hpp"

SortingController::SortingController(SortingModel& model, SortingView& view)
	: Controller(model, view, ApplicationState::Sorting)
{
	view.setAlgorithmComboListSelectCallback([&](SortingAlgorithm algorithm)
		{

		});
}
