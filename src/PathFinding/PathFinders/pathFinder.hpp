#ifndef __PATH_FINDER_HPP
#define __PATH_FINDER_HPP
#include <vector>

class PathFinder
{
public:
	virtual void findPath() = 0;

	void setStart(std::pair<int, int> start);
	void setEnd(std::pair<int, int> end);
private:
	std::pair<int, int> m_start, m_end;
};

#endif