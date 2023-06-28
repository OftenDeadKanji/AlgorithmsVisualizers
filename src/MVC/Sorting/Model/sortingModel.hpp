#ifndef __SORTING_MODEL_HPP__
#define __SORTING_MODEL_HPP__

#include "../../Base/Model/model.hpp"
#include "../../../Sorting/sortingAlgorithm.hpp"
#include "../../../Sorting/Sorters/sorter.hpp"
#include <vector>
#include <string>
#include <memory>

class SortingModel
	: public Model
{
public:
	void update() override;
	void startSorting();

	static std::vector<SortingAlgorithm> getAllAvailableSortingAlgorithms();
	void setSortingAlgorithm(SortingAlgorithm algorithm);
	void setLatency(float latency);
	void setArraySize(int size);
private:
	std::unique_ptr<Sorter> m_sorter;
};

#endif