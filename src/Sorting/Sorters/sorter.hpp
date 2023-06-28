#ifndef __SORTER_HPP__
#define __SORTER_HPP__
#include <vector>
#include <atomic>
#include <mutex>

class Sorter
{
public:
	void sort();
	void pause();
	void resume();

	void setLatency(float latency);
	void setArraySize(int size);

	bool finishedSorting() const;

	void getArrayCopy(std::vector<int>& outCopy);
protected:
	std::vector<int> m_array;
	std::thread m_sortingThread;
	std::mutex m_arrayMutex;

	std::atomic<float> m_latency = 50.0; // in ms
	std::atomic<bool> m_continueSorting {true};
	bool m_finishedSorting = false;
};

#endif