#include "quickSorter.hpp"
#include "../../Utils/Timer/timer.hpp"

QuickSorter::QuickSorter()
	: Sorter(SortingAlgorithm::Quick)
{
}

void QuickSorter::sort()
{
	Timer timer;
	timer.reset();

	quicksort(0, m_array.size() - 1, timer);

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

	m_finishedSorting = true;
	m_isSorting = false;
}

int QuickSorter::getIndex() const
{
	return m_index;
}

void QuickSorter::quicksort(int l, int r, Timer& timer)
{
	if (l < r)
	{
		int i = divide(l, r, timer);

		if (m_stopSorting)
		{
			return;
		}

		while (!m_continueSorting.load());

		quicksort(l, i - 1, timer);

		if (m_stopSorting)
		{
			return;
		}

		while (!m_continueSorting.load());

		quicksort(i + 1, r, timer);
	}
}

int QuickSorter::divide( int l, int r, Timer& timer)
{
	int index = l + (r - l) / 2;
	int value = m_array[index];
	swap(index, r);

	m_index = index;

	if (m_stopSorting)
	{
		return 0;
	}

	while (!m_continueSorting.load());

	while (timer.getTimeInSeconds() < m_latency)
	{
		std::this_thread::yield();
	}
	timer.reset();

	int position = l;

	for (int i = l; i < r; i++)
	{
		m_index = i;

		if (m_array[i] < value)
		{
			swap(i, position);
			position++;

			if (m_stopSorting)
			{
				return 0;
			}

			while (!m_continueSorting.load());

			while (timer.getTimeInSeconds() < m_latency)
			{
				std::this_thread::yield();
			}
			timer.reset();
		}
	}
	swap(position, r);

	m_index = position;

	if (m_stopSorting)
	{
		return 0;
	}

	while (!m_continueSorting.load());

	while (timer.getTimeInSeconds() < m_latency)
	{
		std::this_thread::yield();
	}
	timer.reset();

	return position;
}
