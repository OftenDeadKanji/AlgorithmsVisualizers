#include "pathFinder.hpp"
#include "../board.hpp"

void PathFinder::start(Board& board)
{
	m_finishedFinding = false;
	m_isFinding = true;

	if (m_findingThread.joinable())
	{
		m_findingThread.join();
	}

	m_findingThread = std::thread(&PathFinder::findPath, this, std::ref(board));
}
