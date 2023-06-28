#ifndef __SORTING_ALGORITHM_HPP__
#define __SORTING_ALGORITHM_HPP__
#include <string>

enum class SortingAlgorithm
{
	Bubble
};

constexpr std::string SortingAlgorithmToString(SortingAlgorithm algorithm)
{
	switch (algorithm)
	{
	case SortingAlgorithm::Bubble:
		return "Bubble";
	default:
		return "";
	}
}

#endif