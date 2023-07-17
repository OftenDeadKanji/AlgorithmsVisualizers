#include "pathFinder.hpp"
#include "../board.hpp"

PathFindingAlgorithm PathFinder::getAlgorithm() const
{
	return m_algorithm;
}

void PathFinder::start(Board& board)
{
	m_continueFinding = true;
	m_stopFinding = false;

	m_finishedFinding = false;
	m_isFinding = true;
	if (m_findingThread.joinable())
	{
		m_findingThread.join();
	}

	m_findingThread = std::thread(&PathFinder::findPath, this, std::ref(board));
}

void PathFinder::stop()
{
	m_stopFinding = true;
}

void PathFinder::pause()
{
	m_continueFinding = false;
}

void PathFinder::resume()
{
	m_continueFinding = true;
}

void PathFinder::setDelay(float delay)
{
	m_latency.store(delay);
}

float PathFinder::getDelay() const
{
	return m_latency.load();
}

bool PathFinder::finishedFinding() const
{
	return m_finishedFinding;
}

bool PathFinder::isFinding() const
{
	return m_isFinding;
}

void PathFinder::waitToFinishWorking()
{
	m_continueFinding = true;

	if (m_findingThread.joinable())
	{
		m_findingThread.join();
	}
}

PathFinder::PathFinder(PathFindingAlgorithm algorithm)
	: m_algorithm(algorithm)
{}
