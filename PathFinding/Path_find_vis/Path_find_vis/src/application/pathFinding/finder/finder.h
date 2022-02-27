#pragma once
#include "../graph/graph.h"
#include "inputInfo.h"

namespace PFAV::Core
{
	class Finder
	{
	public:
		enum class Algorithm
		{
			eDijkstra,
			eA_star,
			eBellmanFord,

			eFirst = eDijkstra,
			eLast = eBellmanFord
		};
		
		explicit Finder(InputInfo);
		virtual ~Finder() = default;

		virtual void findPath() = 0;

	protected:
		virtual void updateBoard() = 0;

		InputInfo inputInfo;
		constexpr static Weight INF = DBL_MAX;
		Graph graph;

		unsigned int startNodeNumber, endNodeNumber;
	};
}
