#include "heapSorter.hpp"
#include <algorithm>
#include "../../Utils/Timer/timer.hpp"

HeapSorter::HeapSorter()
	: Sorter(SortingAlgorithm::Heap)
{}

void HeapSorter::sort()
{
	Timer timer;
	timer.reset();

	createHeap(timer);

	for (int i = m_array.size() - 1; i >= 1; i--)
	{
		m_index = i;

		swap(0, i);

		if (m_stopSorting)
		{
			return;
		}

		while (!m_continueSorting.load());

		while (timer.getTimeInSeconds() < m_latency)
		{
			std::this_thread::yield();
		}
		timer.reset();

		shiftDown(i - 1, 0, timer);
		if (m_stopSorting)
		{
			return;
		}
	}

	m_finishedSorting = true;
	m_isSorting = false;
}

int HeapSorter::getIndex() const
{
	return m_index;
}

void HeapSorter::createHeap(Timer& timer)
{
    for (int i = m_array.size() / 2 - 1; i >= 0; i--)
    {
		m_index = i;

		shiftDown(m_array.size(), i, timer);
    }
}

void HeapSorter::shiftDown(int n, int i, Timer& timer)
{
	int j, k = i;
	do
	{
		m_index = j = k;
		if (j * 2 < n && m_array[j * 2] > m_array[k])
		{
			k = j * 2;
		}
		if (j * 2 + 1 < n && m_array[j * 2 + 1] > m_array[k])
		{
			k = j * 2 + 1;
		}

		swap(j, k);

		if (m_stopSorting)
		{
			return;
		}

		while (!m_continueSorting.load());

		while (timer.getTimeInSeconds() < m_latency)
		{
			std::this_thread::yield();
		}
		timer.reset();

	} while (j != k);
}
