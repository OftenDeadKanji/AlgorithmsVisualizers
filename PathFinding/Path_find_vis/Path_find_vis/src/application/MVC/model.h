#pragma once
#include "../pathFinding/finder/finder.h"

namespace PFAV::MVC
{
	class FinderClassNotSetException
		: public std::exception
	{};

	enum class State
	{
		eIdle,
		eStartFindingPath,
		eFindingPath,
		eStopped,

		eClearing,
		eReadyToExit
	};

	class Model
	{
	public:
		Model();

		void update();

		void changeToPreviousAlgorithm();
		void changeToNextAlgorithm();
		Core::Finder::Algorithm getChosenAlgorithm() const;

		void increaseBoardSize();
		void decreaseBoardSize();

		void setTileType(int x, int y, Core::Tile::Type);

		const std::vector<std::vector<Core::Tile>>& getBoard() const;
		void setBoardSize(int size);

		bool canStartFindingPath() const;

		void startFindingPath();
		void stopFindingPath();

		void prepareToExit();
		void reset();
	private:
		void findPath();

		void setNewStartTile(int x, int y);
		void setNewEndTile(int x, int y);
		void setNewOtherTypeTile(int x, int y, Core::Tile::Type);

		int startPosX = -1, startPosY = -1;
		int endPosX = -1, endPosY = -1;
		std::vector<std::vector<Core::Tile>> board;
		bool shouldContinueFindingPath = true;

		Core::Finder::Algorithm chosenAlgorithm = Core::Finder::Algorithm::eDijkstra;

		State state;
		std::thread thread;
	};

}
