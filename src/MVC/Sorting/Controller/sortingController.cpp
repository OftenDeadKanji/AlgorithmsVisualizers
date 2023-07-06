#include "sortingController.hpp"

SortingController::SortingController(SortingModel& model, SortingView& view)
	: Controller(model, view, ApplicationState::Sorting)
{
	view.setAlgorithmSelectCallback([&](SortingAlgorithm algorithm)
		{
			m_model.setSortingAlgorithm(algorithm);
		});

	view.setDelayValueChangeCallback([&](float timeInSec) 
		{
			m_model.setDelay(timeInSec);
		});

	view.setArraySizeChangeCallback([&](int size)
		{
			m_model.setArraySize(size);
		});

	view.setSortStartButtonCallback([&]()
		{
			m_model.startSorting();
		});
	view.setSortPauseButtonCallback([&]()
		{
			m_model.pauseSorting();
		});
	view.setSortResumeButtonCallback([&]()
		{
			m_model.resumeSorting();
		});

	view.setDisplayedDelay(SortingModel::DEFAULT_DELAY);
	view.setDisplayedArraySize(SortingModel::DEFAULT_ARRAY_SIZE);
}
