#include "pch.h"
#include "graphNode.h"

namespace PFAV::Core
{
	GraphNode::GraphNode(unsigned int number, unsigned int x, unsigned int y)
		: number(number), boardPosX(x), boardPosY(y)
	{}

	bool GraphNode::operator==(const GraphNode& other) const
	{
		return this->number == other.number && this->boardPosX == other.boardPosX && this->boardPosY == other.boardPosY;
	}

	bool GraphNode::operator<(const GraphNode& other) const
	{
		return this->number < other.number;
	}
}
