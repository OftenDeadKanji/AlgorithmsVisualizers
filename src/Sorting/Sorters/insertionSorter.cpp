#include "insertionSorter.hpp"
#include "../../Utils/Timer/timer.hpp"

InsertionSorter::InsertionSorter()
	: Sorter(SortingAlgorithm::Insertion)
{}

void InsertionSorter::sort()
{
	m_sortedSize = 1;

	Timer timer;
	timer.reset();

	for (int i = 1; i < m_array.size(); i++)
	{
		for (int j = m_sortedSize - 1; j >= 0; j--)
		{
			m_index = j;

			if (m_array[j] > m_array[j + 1])
			{
				m_arrayMutex.lock();
				{
					std::swap(m_array[j], m_array[j + 1]);
				}
				m_arrayMutex.unlock();
			}
			else
			{
				break;
			}

			if (m_stopSorting)
			{
				return;
			}

			while (!m_continueSorting.load());
			applyDelay(timer.getTimeInSeconds());
			timer.reset();
		}

		m_sortedSize++;

		if (isArraySorted())
		{
			m_finishedSorting = true;
			m_isSorting = false;
			break;
		}
	}
}

int InsertionSorter::getIndex() const
{
	return m_index;
}
