#ifndef __PATH_FINDING_ALGORITHM_HPP__
#define __PATH_FINDING_ALGORITHM_HPP__
#include <string>

enum class PathFindingAlgorithm
{
	None,

	Dijkstra,
	AStar
};

constexpr std::string PathFindingAlgorithmToString(PathFindingAlgorithm algorithm)
{
	switch (algorithm)
	{
	case PathFindingAlgorithm::Dijkstra:
		return "Dijkstra";
	case PathFindingAlgorithm::AStar:
		return "A*";
	default:
		return "";
	}
}

#endif