#include "board.hpp"

Board::Weight& Board::operator()(const std::pair<int, int>& position)
{
	return m_graph[position.first][position.second];
}

void Board::setSize(const std::pair<int, int>& size)
{
	m_graph.resize(size.first);

	for (auto& column : m_graph)
	{
		column.resize(size.second);
	}
}

std::pair<int, int> Board::getSize() const
{
	return std::pair<int, int>();
}
