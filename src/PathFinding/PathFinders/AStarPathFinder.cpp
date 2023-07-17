#include "AStarPathFinder.hpp"
#include "../board.hpp"
#include "../../Utils/Timer/timer.hpp"

AStarPathFinder::AStarPathFinder()
	: PathFinder(PathFindingAlgorithm::AStar)
{}

void AStarPathFinder::findPath(Board& board)
{
	Timer timer;
	timer.reset();

	m_board = &board;

	auto start = board.getStartPosition();
	auto startFlat = board.getStartFlatPosition();

	m_end = board.getEndPosition();
	auto endFlat = board.getEndFlatPosition();

	auto boardSize = board.getSize();
	int cellsCount = boardSize.first * boardSize.second;

	std::vector<std::pair<int, int>> searched, notSearched;
	notSearched.push_back(start);

	std::vector<float> g(cellsCount);
	g[startFlat] = 0.0f;

	std::vector<std::pair<int, int>> previous(cellsCount);

	while (!notSearched.empty())
	{
		std::pair<int, int> x;
		decltype(notSearched)::iterator posIt;
		float xF = std::numeric_limits<float>::max();
		for (auto iter = notSearched.begin(); iter != notSearched.end(); iter++)
		{
			float f = g[board.getFlatPosition(*iter)] + h(*iter);
			if (f < xF)
			{
				x = *iter;
				xF = f;
				posIt = iter;
			}
		}

		if (x == m_end)
		{
			auto currentCell = m_end;
			while (1)
			{
				auto prevCell = previous[board.getFlatPosition(currentCell)];
				if (prevCell == start)
				{
					m_isFinding = false;
					m_finishedFinding = true;

					return;
				}

				board.setPathCell(prevCell);
				currentCell = prevCell;
			}

			return;
		}

		notSearched.erase(posIt);
		searched.push_back(x);

		if (!board.isStartCell(x))
		{
			board.setVisitedCell(x);
		}

		auto neighbours = board.getNeighboursPositions(x);
		for (auto neighbour : neighbours)
		{
			int neighbourFlat = board.getFlatPosition(neighbour);

			if (auto iter = std::find(searched.begin(), searched.end(), neighbour); iter != searched.end())
			{
				continue;
			}

			auto gTemp = g[board.getFlatPosition(x)] + board(x, neighbour);

			bool gTempIsBetter = false;
			if (auto iter = std::find(notSearched.begin(), notSearched.end(), neighbour); iter == notSearched.end())
			{
				notSearched.push_back(neighbour);
				gTempIsBetter = true;
			}
			else if (gTemp < g[neighbourFlat])
			{
				gTempIsBetter = true;
			}

			if (gTempIsBetter)
			{
				previous[neighbourFlat] = x;
				g[neighbourFlat] = gTemp;
			}
		}

		if (m_stopFinding)
		{
			m_isFinding = false;
			return;
		}

		while (!m_continueFinding.load());

		while (timer.getTimeInSeconds() < m_latency)
		{
			std::this_thread::yield();
		}

		timer.reset();
	}
}

float AStarPathFinder::h(std::pair<int, int> position)
{
	if (m_board->isObstacleCell(position))
	{
		return std::numeric_limits<float>::infinity();
	}

	return sqrtf(powf(position.first - m_end.first, 2.0f) + powf(position.second - m_end.second, 2.0f));
}
