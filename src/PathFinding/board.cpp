#include "board.hpp"

Board::Weight& Board::operator()(const std::pair<int, int>& from, const std::pair<int, int>& to)
{
	int fromFlat = getFlatPosition(from);
	int toFlat = getFlatPosition(to);

	return m_weightGraph[fromFlat][toFlat];
}

const Board::Weight& Board::operator()(const std::pair<int, int>& from, const std::pair<int, int>& to) const
{
	return this->operator()(from, to);
	//int fromFlat = getFlatPosition(from);
	//int toFlat = getFlatPosition(to);
	//
	//return m_graph[fromFlat][toFlat];
}

Board::Weight& Board::operator()(int xFrom, int yFrom, int xTo, int yTo)
{
	return this->operator()(std::make_pair(xFrom, yFrom), std::make_pair(xTo, yTo));
	//int fromFlat = getFlatPosition(xFrom, yFrom);
	//int toFlat = getFlatPosition(xTo, yTo);
	//
	//return m_graph[fromFlat][toFlat];
}

const Board::Weight& Board::operator()(int xFrom, int yFrom, int xTo, int yTo) const
{
	return this->operator()(std::make_pair(xFrom, yFrom), std::make_pair(xTo, yTo));
	//int fromFlat = getFlatPosition(xFrom, yFrom);
	//int toFlat = getFlatPosition(xTo, yTo);
	//
	//return m_graph[fromFlat][toFlat];
}

void Board::setSize(const std::pair<int, int>& size)
{
	m_size = size;

	m_weightGraph.resize(size.first * size.second);
	for (auto& column : m_weightGraph)
	{
		column.resize(size.first * size.second);
		for (auto& weight : column)
		{
			weight = std::numeric_limits<Weight>::infinity();
		}
	}

	m_cells.resize(size.first);
	for (auto& column : m_cells) 
	{
		column.resize(size.second);
		for(auto& cell : column)
		{
			cell = CellType::Normal;
		}
	}

}

std::pair<int, int> Board::getSize() const
{
	return m_size;
}

void Board::setNormalCell(const std::pair<int, int>& position)
{
	//int posFlat = getFlatPosition(position);
	//auto neighbours = getNeighboursFlatPositions(position);
	//
	//for (auto& neighbour : neighbours)
	//{
	//	m_weightGraph[neighbour][posFlat] = NormalWeight;
	//}

	m_cells[position.first][position.second] = CellType::Normal;
}

void Board::setNormalCell(int x, int y)
{
	setNormalCell(std::make_pair(x, y));
}

bool Board::isNormalCell(const std::pair<int, int>& position) const
{
	//int positionFlat = getFlatPosition(position);
	//
	//auto neighbours = getNeighboursFlatPositions(position);
	//for(auto& neighbour : neighbours)
	//{
	//	if (abs(m_weightGraph[neighbour][positionFlat] - NormalWeight) < 0.0001)
	//	{
	//		return false;
	//	}
	//}

	return m_cells[position.first][position.second] == CellType::Normal;
}

bool Board::isNormalCell(int x, int y) const
{
	return isNormalCell(std::make_pair(x, y));
}

void Board::setObstacleCell(const std::pair<int, int>& position)
{
	//int posFlat = getFlatPosition(position);
	//auto neighbours = getNeighboursFlatPositions(position);
	//
	//for (auto& neighbour : neighbours)
	//{
	//	m_weightGraph[neighbour][posFlat] = ObstacleWeight;
	//}

	m_cells[position.first][position.second] = CellType::Obstacle;
}

void Board::setObstacleCell(int x, int y)
{
	setObstacleCell(std::make_pair(x, y));
}

bool Board::isObstacleCell(const std::pair<int, int>& position) const
{
	//int positionFlat = getFlatPosition(position);
	//
	//auto neighbours = getNeighboursFlatPositions(position);
	//for (auto& neighbour : neighbours)
	//{
	//	if (abs(m_weightGraph[neighbour][positionFlat] - ObstacleWeight) < 0.0001)
	//	{
	//		return false;
	//	}
	//}
	//return true;

	return m_cells[position.first][position.second] == CellType::Obstacle;
}

bool Board::isObstacleCell(int x, int y) const
{
	return isObstacleCell(std::make_pair(x, y));
}

void Board::setStartCell(const std::pair<int, int>& position)
{
	if (m_start.first >= 0 && m_start.first < m_size.first && m_start.second >= 0 && m_start.second < m_size.second)
	{
		m_cells[m_start.first][m_start.second] = CellType::Normal;
	}

	m_start = position;
	m_cells[m_start.first][m_start.second] = CellType::Start;
}

void Board::setStartCell(int x, int y)
{
	setStartCell(std::make_pair(x, y));
}

bool Board::isStartCell(const std::pair<int, int>& position) const
{
	return m_cells[position.first][position.second] == CellType::Start;
}

bool Board::isStartCell(int x, int y) const
{
	return isStartCell(std::make_pair(x, y));
}

std::pair<int, int> Board::getStartPosition() const
{
	return m_start;
}

int Board::getStartFlatPosition() const
{
	return getFlatPosition(m_start);
}

void Board::setEndCell(const std::pair<int, int>& position)
{
	if (m_end.first >= 0 && m_end.first < m_size.first && m_end.second >= 0 && m_end.second < m_size.second)
	{
		m_cells[m_end.first][m_end.second] = CellType::Normal;
	}

	m_end = position;
	m_cells[m_end.first][m_end.second] = CellType::End;
}

void Board::setEndCell(int x, int y)
{
	setEndCell(std::make_pair(x, y));
}

bool Board::isEndCell(const std::pair<int, int>& position) const
{
	return m_cells[position.first][position.second] == CellType::End;
}

bool Board::isEndCell(int x, int y) const
{
	return isEndCell(std::make_pair(x, y));
}

std::pair<int, int> Board::getEndtPosition() const
{
	return m_end;
}

int Board::getEndFlatPosition() const
{
	return getFlatPosition(m_end);
}

void Board::setVisitedCell(const std::pair<int, int>& position)
{
	m_cells[position.first][position.second] = CellType::Searched;
}

void Board::setVisitedCell(int x, int y)
{
	setVisitedCell(std::make_pair(x, y));
}

bool Board::isVisitedCell(const std::pair<int, int>& position) const
{
	return m_cells[position.first][position.second] == CellType::Searched;;
}

bool Board::isVisitedCell(int x, int y) const
{
	return isVisitedCell(std::make_pair(x, y));
}

void Board::setPathCell(const std::pair<int, int>& position)
{
	m_cells[position.first][position.second] = CellType::Path;
}

void Board::setPathCell(int x, int y)
{
	setPathCell(std::make_pair(x, y));
}

bool Board::isPathCell(const std::pair<int, int>& position) const
{
	return m_cells[position.first][position.second] == CellType::Path;
}

bool Board::isPathCell(int x, int y) const
{
	return isPathCell(std::make_pair(x, y));
}

std::vector<std::pair<int, int>> Board::getNeighboursPositions(std::pair<int, int> cellPosition) const
{
	std::vector<std::pair<int, int>> neighbours;

	if (cellPosition.first > 0)
	{
		neighbours.push_back(std::make_pair(cellPosition.first - 1, cellPosition.second));

		if (cellPosition.second > 0)
		{
			neighbours.push_back(std::make_pair(cellPosition.first - 1, cellPosition.second - 1));
		}
		if (cellPosition.second < m_size.second - 1)
		{
			neighbours.push_back(std::make_pair(cellPosition.first - 1, cellPosition.second + 1));
		}
	}
	if (cellPosition.first < m_size.first - 1)
	{
		neighbours.push_back(std::make_pair(cellPosition.first + 1, cellPosition.second));

		if (cellPosition.second > 0)
		{
			neighbours.push_back(std::make_pair(cellPosition.first + 1, cellPosition.second - 1));
		}
		if (cellPosition.second < m_size.second - 1)
		{
			neighbours.push_back(std::make_pair(cellPosition.first + 1, cellPosition.second + 1));
		}
	}
	if (cellPosition.second > 0)
	{
		neighbours.push_back(std::make_pair(cellPosition.first, cellPosition.second - 1));
	}
	if (cellPosition.second < m_size.second - 1)
	{
		neighbours.push_back(std::make_pair(cellPosition.first, cellPosition.second + 1));
	}
	return neighbours;
}

std::vector<std::pair<int, int>> Board::getNeighboursPositions(int x, int y) const
{
	return getNeighboursPositions(std::make_pair(x, y));
}

int Board::getFlatPosition(const std::pair<int, int>& position) const
{
	return position.first * m_size.second + position.second;
}

int Board::getFlatPosition(int x, int y) const
{
	return x * m_size.second + y;
}

std::vector<int> Board::getNeighboursFlatPositions(std::pair<int, int> cellPosition) const
{
	auto neighbours = getNeighboursPositions(cellPosition);
	std::vector<int> neighboursFlat;
	for (auto& neighbour : neighbours)
	{
		neighboursFlat.push_back(getFlatPosition(neighbour));
	}

	return neighboursFlat;
}

std::vector<int> Board::getNeighboursFlatPositions(int x, int y) const
{
	return getNeighboursFlatPositions(std::make_pair(x, y));
}

void Board::initWeights()
{
	for (auto& column : m_weightGraph)
	{
		for (auto& weight : column)
		{
			weight = ObstacleWeight;
		}
	}

	for (int i = 0; i < m_size.first; i++)
	{
		for (int j = 0; j < m_size.second; j++)
		{
			auto pos = std::make_pair(i, j);
			auto posFlat = getFlatPosition(pos);

			if (m_cells[i][j] != CellType::Obstacle)
			{
				m_weightGraph[posFlat][posFlat] = 0.0;

				auto neighbours = getNeighboursPositions(pos);
				for (auto& neighbour : neighbours)
				{
					int neighbourFlat = getFlatPosition(neighbour);

					if (isObstacleCell(neighbour))
					{
						m_weightGraph[posFlat][neighbourFlat] = ObstacleWeight;
					}
					else if (pos.first - neighbour.first != 0 && pos.second - neighbour.second != 0)
					{
						m_weightGraph[posFlat][neighbourFlat] = DiagonalWeight;
					}
					else
					{
						m_weightGraph[posFlat][neighbourFlat] = NormalWeight;
					}
				}
			}
		}
	}
}

void Board::semiClear()
{
	for (auto& column : m_cells)
	{
		for (auto& cell : column)
		{
			if (cell == CellType::Searched || cell == CellType::Path)
			{
				cell = CellType::Normal;
			}
		}
	}
}