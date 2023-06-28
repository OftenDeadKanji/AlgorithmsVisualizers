#ifndef __ALGORITHM_SELECTOR_HPP__
#define __ALGORITHM_SELECTOR_HPP__
#include <string>
#include <vector>
#include <functional>
#include "../../../Sorting/sortingAlgorithm.hpp"

class AlgorithmSelector
{
public:
	void setAvailableAlgorithms(const std::vector<SortingAlgorithm>& algorithms);
	void updateAndDisplaySelector();
	void setAlgorithmComboListSelectCallback(std::function<void(SortingAlgorithm)> callback);
private:
	std::vector<SortingAlgorithm> m_availableAlgorithms;
	std::vector<std::string> m_availableAlgorithmsNames;
	size_t m_currentlyChosenAlgorithm = 0;

	std::function<void(SortingAlgorithm)> m_callback_onAlgorithmComboListSelect;
};

#endif