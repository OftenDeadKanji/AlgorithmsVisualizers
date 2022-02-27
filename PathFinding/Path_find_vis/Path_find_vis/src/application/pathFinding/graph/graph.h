#pragma once
#include <exception>
#include "graphNode.h"
#include "../tile/tile.h"

namespace PFAV::Core
{

#pragma region constexpr sqrt
	// thank you Stackoverflow, user Alex Shtof
	// https://stackoverflow.com/questions/8622256/in-c11-is-sqrt-defined-as-constexpr
	// :)
	namespace Detail
	{
		double constexpr sqrtNewtonRaphson(double x, double curr, double prev)
		{
			return curr == prev
				? curr
				: sqrtNewtonRaphson(x, 0.5 * (curr + x / curr), curr);
		}
	}

	/*
	* Constexpr version of the square root
	* Return value:
	*   - For a finite and non-negative value of "x", returns an approximation for the square root of "x"
	*   - Otherwise, returns NaN
	*/
	double constexpr sqrt(double x)
	{
		return x >= 0 && x < std::numeric_limits<double>::infinity()
			? Detail::sqrtNewtonRaphson(x, x, 0)
			: std::numeric_limits<double>::quiet_NaN();
	}
#pragma endregion

	using Weight = double;
	constexpr Weight INF = DBL_MAX;

	class GraphNodeNotFound final
		: public std::exception
	{
	public:
		explicit GraphNodeNotFound(const char* message)
			: std::exception(message)
		{}
	};

	class Graph
	{
	public:
		Graph() = default;

		void initializeGraph(const std::vector<std::vector<Tile>>& board, bool withDiagonalNeighbours = true);

		Weight& operator()(const GraphNode& from, const GraphNode& to);
		Weight& operator()(unsigned int from, unsigned int to);

		size_t getSize() const;

		std::vector<const GraphNode*> getNodeNeighbours(const GraphNode& node);
		std::vector<const GraphNode*> getNodeNeighbours(unsigned int nodeNumber);

		void clear();
	private:
		void initNodes(const std::vector<std::vector<Tile>>& board);
		void initWeights(const std::vector<std::vector<Tile>>& board, bool withDiagonalNeighbours);

		size_t size = -1;

		std::set<GraphNode> nodes;
		std::vector<std::vector<Weight>> weights;

		static constexpr Weight defaultNeighbourWeight = 1.0;
		static constexpr Weight diagonalNeighbourWeight = sqrt(2);
	};
}