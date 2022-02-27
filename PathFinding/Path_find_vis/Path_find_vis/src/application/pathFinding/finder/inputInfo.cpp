#include "pch.h"
#include "inputInfo.h"

namespace PFAV::Core
{
	InputInfo::InputInfo(unsigned int startX, unsigned int startY, unsigned int endX, unsigned int endY, std::vector<std::vector<Tile>>& board, const bool& continueCondition)
							 : startPosX(startX), startPosY(startY), endPosX(endX), endPosY(endY), board(board), continueCondition(continueCondition)
	{}
}