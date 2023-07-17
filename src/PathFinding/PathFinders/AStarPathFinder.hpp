#ifndef __A_STAR_PATH_FINDER_HPP__
#define __A_STAR_PATH_FINDER_HPP__
#include "pathFinder.hpp"

class AStarPathFinder
	: public PathFinder
{
public:
	AStarPathFinder();

	void findPath(Board& board) override;
private:
	float h(std::pair<int, int> position);

	std::pair<int, int> m_end;
	Board* m_board;
};

#endif