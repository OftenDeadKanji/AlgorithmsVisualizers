#ifndef __DIJKSTRA_PATH_FINDER_HPP__
#define __DIJKSTRA_PATH_FINDER_HPP__
#include "pathFinder.hpp"

class DijkstraFinder
	: public PathFinder
{
public:
	DijkstraFinder();

	void findPath(Board& board) override;
};

#endif