#pragma once
#include "../tile/tile.h"

namespace PFAV::Core
{
	struct InputInfo
	{
		InputInfo(unsigned int startX, unsigned int startY, unsigned int endX, unsigned int endY, std::vector<std::vector<Tile>>& board, const bool& continueCondition);

		unsigned int startPosX, startPosY;
		unsigned int endPosX, endPosY;

		std::vector<std::vector<Tile>>& board;
		const bool& continueCondition;
	};
}
