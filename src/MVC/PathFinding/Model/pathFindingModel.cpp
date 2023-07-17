#include "pathFindingModel.hpp"
#include "../../../PathFinding/PathFinders/dijkstraPathFinder.hpp"
#include "../../../PathFinding/PathFinders/AStarPathFinder.hpp"

PathFindingModel::PathFindingModel()
{
	setBoardSize(DEFAULT_BOARD_SIZE);

	auto algorithms = getAllAvailablePathFindingAlgorithms();
	if (!algorithms.empty())
	{
		setAlgorithm(algorithms[0]);
	}
}

void PathFindingModel::update()
{}

void PathFindingModel::startFindingPath()
{
	m_board.semiClear();
	m_board.initWeights();

	if (m_pathFinder)
	{
		m_pathFinder->setDelay(m_delay);
		m_pathFinder->start(m_board);
	}
}

void PathFindingModel::stopFindingPath()
{
	if (m_pathFinder)
	{
		m_pathFinder->stop();
	}
}

void PathFindingModel::pauseFindingPath()
{
	if (m_pathFinder)
	{
		m_pathFinder->pause();
	}
}

void PathFindingModel::resumeFindingPath()
{
	if (m_pathFinder)
	{
		m_pathFinder->resume();
	}
}

void PathFindingModel::setDelay(float delay)
{
	m_delay = delay;
	if (m_pathFinder)
	{
		m_pathFinder->setDelay(m_delay);
	}
}

float PathFindingModel::getDelay() const
{
	return m_delay;
}

std::vector<PathFindingAlgorithm> PathFindingModel::getAllAvailablePathFindingAlgorithms()
{
	return {
		PathFindingAlgorithm::Dijkstra,
		PathFindingAlgorithm::AStar
	};
}

void PathFindingModel::setAlgorithm(PathFindingAlgorithm algorithm)
{
	if (m_pathFinder)
	{
		m_pathFinder->stop();
		m_pathFinder->waitToFinishWorking();
	}

	switch (algorithm)
	{
	case PathFindingAlgorithm::Dijkstra:
		m_pathFinder = std::make_unique<DijkstraFinder>();
		break;
	case PathFindingAlgorithm::AStar:
		m_pathFinder = std::make_unique<AStarPathFinder>();
	}
}

PathFindingAlgorithm PathFindingModel::getCurrentAlgorithm() const
{
	return m_pathFinder ? m_pathFinder->getAlgorithm() : PathFindingAlgorithm::None;
}

bool PathFindingModel::isFindingPath() const
{
	return m_pathFinder ? m_pathFinder->isFinding() : false;
}

void PathFindingModel::setStartCell(const std::pair<int, int>& position)
{
	auto size = m_board.getSize();
	if (position.first >= 0 && position.first < size.first && position.second >= 0 && position.second < size.second)
	{
		//m_startCell = position;
		m_board.setStartCell(position);
	}
}

bool PathFindingModel::isStartCell(const std::pair<int, int>& position) const
{
	return m_startCell == position;
}

void PathFindingModel::setEndCell(const std::pair<int, int>& position)
{
	auto size = m_board.getSize();
	if (position.first >= 0 && position.first < size.first && position.second >= 0 && position.second < size.second)
	{
		//m_endCell = position;
		m_board.setEndCell(position);
	}
}

bool PathFindingModel::isEndCell(const std::pair<int, int>& position) const
{
	return m_endCell == position;
}

void PathFindingModel::setNormalCell(const std::pair<int, int>& position)
{
	auto size = m_board.getSize();
	if (position.first >= 0 && position.first < size.first && position.second >= 0 && position.second < size.second)
	{
		m_board.setNormalCell(position);
	}
}

void PathFindingModel::setObstacleCell(const std::pair<int, int>& position)
{
	auto size = m_board.getSize();
	if (position.first >= 0 && position.first < size.first && position.second >= 0 && position.second < size.second)
	{
		m_board.setObstacleCell(position);
	}
}

const std::pair<int, int>& PathFindingModel::getBoardSize() const
{
	return m_board.getSize();
}

void PathFindingModel::setBoardSize(const std::pair<int, int>& size)
{
	m_board.setSize(size);
}

const Board& PathFindingModel::getBoard() const
{
	return m_board;
}
