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
	SortingModel();

	void update() override;
	void startSorting();
	void pauseSorting();
	void resumeSorting();

	static std::vector<SortingAlgorithm> getAllAvailableSortingAlgorithms();
	void setSortingAlgorithm(SortingAlgorithm algorithm);
	SortingAlgorithm getCurrentSortingAlgorithmName() const;

	void setDelay(float delay);
	float getDelay() const;
	static constexpr float DEFAULT_DELAY = 0.0001f;

	void setArraySize(int size);

	void getArrayCopy(std::vector<int>& sortingArray) const;
	const std::vector<int>& getArray() const;
	static constexpr int MAX_ARRAY_SIZE = 100000;
	static constexpr int DEFAULT_ARRAY_SIZE = 500;

	int getIndex() const;

	bool isSorting() const;
	bool finishedSorting() const;
private:
	std::unique_ptr<Sorter> m_sorter;
	float m_sortingDelay = DEFAULT_DELAY;
	int m_arraySize = DEFAULT_ARRAY_SIZE;
};

#endif