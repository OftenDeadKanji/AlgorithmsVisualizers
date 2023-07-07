#ifndef __PATH_FINDING_ALGORITHM_HPP__
#define __PATH_FINDING_ALGORITHM_HPP__
#include <string>

enum class PathFindingAlgorithm
{
	None,
};

constexpr std::string PathFindingAlgorithmToString(PathFindingAlgorithm algorithm)
{
	switch (algorithm)
	{
	default:
		return "";
	}
}

#endif