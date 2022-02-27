#pragma once

namespace PFAV::Core
{
	struct GraphNode
	{
		GraphNode(unsigned int number, unsigned int x, unsigned int y);

		bool operator==(const GraphNode& other) const;
		bool operator<(const GraphNode& other) const;

		const unsigned int number = -1;
		const unsigned int boardPosX = -1, boardPosY = -1;
	};
}