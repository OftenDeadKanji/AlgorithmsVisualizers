#include "bubbleSorter.hpp"
#include "../../Utils/Timer/timer.hpp"

BubbleSorter::BubbleSorter()
	: Sorter(SortingAlgorithm::Bubble)
{
}

void BubbleSorter::sort()
{
	Timer timer;
	timer.reset();

	while (true)
	{

		for (m_index = 1; m_index < m_array.size(); m_index++)
		{
			if (m_array[m_index] < m_array[m_index - 1])
			{
				m_arrayMutex.lock();
				{
					std::swap(m_array[m_index], m_array[m_index - 1]);
				}
				m_arrayMutex.unlock();
			}

			if (m_stopSorting)
			{
				return;
			}

			while (!m_continueSorting.load());
			applyDelay(timer.getTimeInSeconds());
			timer.reset();

		}

		if (isArraySorted())
		{
			m_finishedSorting = true;
			m_isSorting = false;
			break;
		}
	}
}

int BubbleSorter::getIndex() const
{
	return m_index;
}
