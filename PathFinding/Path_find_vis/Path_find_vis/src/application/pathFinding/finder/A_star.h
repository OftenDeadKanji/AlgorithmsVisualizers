#pragma once

namespace PFAV::Core
{
	class A_star final
		: public Finder
	{
	public:
		explicit A_star(InputInfo);

		void findPath() override;
		void updateBoard() override;
		void init();

	private:
		std::vector<int> getNodeNeighbours(int nodeNumber);

		std::set<int> closedSet;
		std::set<int> openSet;
		std::vector<float> g_score;
		std::vector<float> h_score;

		std::vector<int> previousNode;

		std::vector<std::pair<int, Tile::Type>> boardTilesToUpdate;
	};
}

