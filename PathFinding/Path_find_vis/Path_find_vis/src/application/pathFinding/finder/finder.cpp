#include "pch.h"
#include "finder.h"

namespace PFAV::Core
{
	Finder::Finder(InputInfo info)
		: inputInfo(info)
	{
		this->graph.initializeGraph(info.board, true);

		this->startNodeNumber = info.startPosY + info.startPosX * info.board.size();
		this->endNodeNumber = info.endPosY + info.endPosX * info.board.size();
	}
}

