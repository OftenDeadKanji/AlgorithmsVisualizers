#ifndef __SORTING_ALGORITHM_HPP__
#define __SORTING_ALGORITHM_HPP__
#include <string>

enum class SortingAlgorithm
{
	None,

	Bubble,
	Insertion,
	Quick
};

constexpr std::string SortingAlgorithmToString(SortingAlgorithm algorithm)
{
	switch (algorithm)
	{
	case SortingAlgorithm::Bubble:
		return "Bubble";
	case SortingAlgorithm::Insertion:
		return "Insertion";
	case SortingAlgorithm::Quick:
		return "Quick";
	default:
		return "";
	}
}

#endif