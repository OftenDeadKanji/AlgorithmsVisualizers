#include "dijkstraPathFinder.hpp"
#include "../../Utils/Timer/timer.hpp"
#include "../board.hpp"
#include <queue>

DijkstraFinder::DijkstraFinder()
	: PathFinder(PathFindingAlgorithm::Dijkstra)
{}

void DijkstraFinder::findPath(Board& board)
{
	Timer timer;
	timer.reset();

	auto boardSize = board.getSize();
	int boardCellsCount = boardSize.first * boardSize.second;

	std::vector<std::vector<Board::Weight>> distanceToStart;
	std::vector<std::vector<std::pair<int, int>>> previous;

	auto priorityFunc = [&](const std::pair<int, int>& l, const std::pair<int, int>& r)
	{
		return distanceToStart[l.first][l.second] > distanceToStart[r.first][r.second];
	};
	std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, decltype(priorityFunc)> queue(priorityFunc);
	decltype(queue) queueCopy(priorityFunc);

	distanceToStart.resize(boardSize.first);
	previous.resize(boardSize.first);

	auto start = board.getStartPosition();
	auto end = board.getEndtPosition();
	int startFlat = board.getStartFlatPosition();
	for (int i = 0; i < boardSize.first; i++)
	{
		distanceToStart[i].resize(boardSize.second);
		previous[i].resize(boardSize.second);

		for (int j = 0; j < boardSize.second; j++)
		{
			if (std::make_pair(i, j) == start)
			{
				distanceToStart[start.first][start.second] = 0.0;
			}
			else
			{
				distanceToStart[i][j] = std::numeric_limits<double>::infinity();
			}

			previous[i][j] = std::make_pair(-1, -1);
			queue.push(std::make_pair(i, j));

			if (m_stopFinding)
			{
				m_isFinding = false;
				return;
			}

			while (!m_continueFinding.load());
		}
	}


	while (!queue.empty())
	{
		//update q
		while (!queue.empty())
		{
			auto elem = queue.top();
			queue.pop();

			queueCopy.push(elem);
		}

		while (!queueCopy.empty())
		{
			auto elem = queueCopy.top();
			queueCopy.pop();

			queue.push(elem);
		}

		if (m_stopFinding)
		{
			m_isFinding = false;
			return;
		}

		while (!m_continueFinding.load());

		auto u = queue.top();
		queue.pop();

		if (u != start)
		{
			board.setVisitedCell(u);
		}

		auto neighbours = board.getNeighboursPositions(u);
		for (auto& neighbour : neighbours)
		{
			if (distanceToStart[neighbour.first][neighbour.second] > distanceToStart[u.first][u.second] + board(u, neighbour))
			{
				distanceToStart[neighbour.first][neighbour.second] = distanceToStart[u.first][u.second] + board(u, neighbour);
				previous[neighbour.first][neighbour.second] = u;

				if (neighbour == end)
				{
					auto currentCell = end;
					while (1)
					{
						auto prevCell = previous[currentCell.first][currentCell.second];
						if (prevCell == start)
						{
							m_isFinding = false;
							m_finishedFinding = true;

							return;
						}

						board.setPathCell(prevCell);
						currentCell = prevCell;
					}
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
}
