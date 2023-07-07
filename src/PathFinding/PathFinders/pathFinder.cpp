#include "pathFinder.hpp"

void PathFinder::setStart(std::pair<int, int> start)
{
	m_start = std::move(start);
}

void PathFinder::setEnd(std::pair<int, int> end)
{
	m_end = std::move(end);
}
