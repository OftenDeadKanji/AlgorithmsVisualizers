#ifndef __SORTER_HPP__
#define __SORTER_HPP__
#include <vector>
#include <atomic>
#include <mutex>
#include "../sortingAlgorithm.hpp"

class Sorter
{
public:
	void start();
	void stop();
	void pause();
	void resume();
	virtual void sort() = 0;

	void setDelay(float delay);
	float getDelay() const;

	void setArraySize(int size);

	bool finishedSorting() const;
	bool isSorting() const;
	void waitToFinishWorking();

	void getArrayCopy(std::vector<int>& outCopy);
	const std::vector<int>& getArray() const;
	virtual int getIndex() const = 0;

	SortingAlgorithm getAlgorithmName() const;
protected:
	Sorter(SortingAlgorithm algorithmName);

	void swap(int i0, int i1);

	bool isArraySorted() const;
	void applyDelay(float currentIterationTime);

	const SortingAlgorithm m_algorithmName;

	std::vector<int> m_array;
	std::thread m_sortingThread;
	std::mutex m_arrayMutex;

	std::atomic<float> m_latency = 0.0005f; // in s
	std::atomic<bool> m_continueSorting = true; // set to true to make Sorter stop (!= pause) working
	std::atomic<bool> m_stopSorting = false;
	bool m_isSorting = false;
	bool m_finishedSorting = false;
};

#endif