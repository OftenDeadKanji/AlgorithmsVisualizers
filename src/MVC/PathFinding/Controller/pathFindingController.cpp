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

	m_view.setDelayChangeCallback([&](float delay)
		{
			m_model.setDelay(delay);
		});

	m_view.setStartCellAddCallback([&](std::pair<int, int> position)
		{
			model.setStartCell(position);
		});
	m_view.setEndCellAddCallback([&](std::pair<int, int> position)
		{
			model.setEndCell(position);
		});
	m_view.setNormalCellAddCallback([&](std::pair<int, int> position)
		{
			model.setNormalCell(position);
		});
	m_view.setObstacleCellAddCallback([&](std::pair<int, int> position)
		{
			model.setObstacleCell(position);
		});

	m_view.setStartButtonCallback([&]()
		{
			model.startFindingPath();
		});
	m_view.setStopButtonCallback([&]()
		{
			model.stopFindingPath();
		});
	m_view.setPauseButtonCallback([&]()
		{
			model.pauseFindingPath();
		});
	m_view.setResumeButtonCallback([&]()
		{
			model.resumeFindingPath();
		});

	m_view.setDisplayedBoardSize(PathFindingModel::DEFAULT_BOARD_SIZE);
}
