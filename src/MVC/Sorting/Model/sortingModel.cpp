#include "sortingModel.hpp"
#include "../../../Sorting/Sorters/bubbleSorter.hpp"
#include <numeric>

SortingModel::SortingModel()
{
	auto algorithms = SortingModel::getAllAvailableSortingAlgorithms();
	if (!algorithms.empty())
	{
		setSortingAlgorithm(algorithms[0]);
	}
}

void SortingModel::update()
{
}

void SortingModel::startSorting()
{
	if (m_sorter)
	{
		m_sorter->setArraySize(m_arraySize);
		m_sorter->setDelay(m_sortingDelay);
		m_sorter->start();
	}
}

void SortingModel::pauseSorting()
{
	if (m_sorter)
	{
		m_sorter->pause();
	}
}

void SortingModel::resumeSorting()
{
	if (m_sorter)
	{
		m_sorter->resume();
	}
}

std::vector<SortingAlgorithm> SortingModel::getAllAvailableSortingAlgorithms()
{
	return { SortingAlgorithm::Bubble };
}

void SortingModel::setSortingAlgorithm(SortingAlgorithm algorithm)
{
	if (m_sorter && m_sorter->getAlgorithmName() != algorithm)
	{
		m_sorter->stop();
		m_sorter->waitToFinishWorking();
	}

	switch (algorithm)
	{
	case SortingAlgorithm::Bubble:
		m_sorter = std::make_unique<BubbleSorter>();
		break;
	}
}

SortingAlgorithm SortingModel::getCurrentSortingAlgorithmName() const
{
	return m_sorter ? m_sorter->getAlgorithmName() : SortingAlgorithm::None;
}

void SortingModel::setDelay(float delay)
{
	m_sortingDelay = delay;
	if (m_sorter)
	{
		m_sorter->setDelay(delay);
	}
}

float SortingModel::getDelay() const
{
	if (m_sorter)
	{
		return m_sorter->getDelay();
	}

	return std::numeric_limits<float>::infinity();
}

void SortingModel::setArraySize(int size)
{
	m_arraySize = size;
	//if (m_sorter)
	//{
	//	m_sorter->setArraySize(size);
	//}
}

void SortingModel::getArrayCopy(std::vector<int>& sortingArray) const
{
	if (m_sorter)
	{
		m_sorter->getArrayCopy(sortingArray);
	}
}

int SortingModel::getIndex() const
{
	return m_sorter->getIndex();
}

bool SortingModel::isSorting() const
{
	return m_sorter ? m_sorter->isSorting() : false;
}

bool SortingModel::finishedSorting() const
{
	return m_sorter ? m_sorter->finishedSorting() : false;
}
