#ifndef __BOARD_HPP__
#define __BOARD_HPP__
#include <vector>
#include <utility>
#include <limits>

class Board
{
public:
	using Weight = double;
	static constexpr Weight NormalWeight = 1.0;
	static constexpr Weight DiagonalWeight = 1.0;
	static constexpr Weight ObstacleWeight = std::numeric_limits<double>::max();

	Weight& operator()(const std::pair<int, int>& position);

	void setSize(const std::pair<int, int>& size);
	std::pair<int, int> getSize() const;

private:
	std::vector<std::vector<Weight>> m_graph;
};

#endif