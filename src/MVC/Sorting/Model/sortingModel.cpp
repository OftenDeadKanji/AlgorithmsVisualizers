#include "sortingModel.hpp"

void SortingModel::update()
{
}

std::vector<SortingAlgorithm> SortingModel::getAllAvailableSortingAlgorithms()
{
	return { SortingAlgorithm::Bubble };
}
