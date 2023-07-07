#include "pathFindingModel.hpp"

void PathFindingModel::update()
{}

std::vector<PathFindingAlgorithm> PathFindingModel::getAllAvailablePathFindingAlgorithms()
{
	return {
		
	};
}

void PathFindingModel::setAlgorithm(PathFindingAlgorithm algorithm)
{
	switch (algorithm)
	{
		
	}
}

void PathFindingModel::setStartCell(const std::pair<int, int>& position)
{
	m_pathFinder->setStart(position);
}

void PathFindingModel::setEndCell(const std::pair<int, int>& position)
{
	m_pathFinder->setEnd(position);
}

void PathFindingModel::setNormalCell(const std::pair<int, int>& position)
{
	m_board(position) = Board::NormalWeight;
}

void PathFindingModel::setObstacleCell(const std::pair<int, int>& position)
{
	m_board(position) = Board::ObstacleWeight;
}

const std::pair<int, int>& PathFindingModel::getBoardSize() const
{
	return m_board.getSize();
}

void PathFindingModel::setBoardSize(const std::pair<int, int>& size)
{
	m_board.setSize(size);
}
