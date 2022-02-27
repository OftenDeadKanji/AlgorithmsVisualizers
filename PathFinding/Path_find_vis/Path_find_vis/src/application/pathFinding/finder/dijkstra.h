#pragma once
#include "finder.h"

namespace PFAV::Core
{
	class Dijkstra final
		: public Finder
	{
	public:
		explicit Dijkstra(InputInfo);

		void findPath() override;
		void updateBoard() override;
		void init();

	private:
		std::vector<double> d;
		std::priority_queue<int, std::vector<int>, std::function<bool(int, int)>> Q;
		std::priority_queue<int, std::vector<int>, std::function<bool(int, int)>> Q_copy;

		std::vector<int> previous;

		std::vector<std::pair<int, Tile::Type>> boardTilesToUpdate;
	};
}
