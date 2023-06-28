#include "sorter.hpp"
#include "../../Utils/Random/random.hpp"

void Sorter::start()
{
	Random::getInstancePtr()->shuffle(m_array);

	m_finishedSorting = false;
	m_isSorting = true;

	if (m_sortingThread.joinable())
	{
		m_sortingThread.join();
	}

	m_sortingThread = std::thread(&Sorter::sort, this);
}

void Sorter::stop()
{
	m_stopSorting.store(true);
}

void Sorter::pause()
{
	m_continueSorting.store(false);
}

void Sorter::resume()
{
	m_continueSorting.store(true);
}

void Sorter::setDelay(float delay)
{
	m_latency.store(delay);
}

float Sorter::getDelay() const
{
	return m_latency.load();
}

void Sorter::setArraySize(int size)
{
	m_finishedSorting = false;

	auto* random = Random::getInstancePtr();

	int currentSize = m_array.size();

	if (currentSize > size)
	{
		m_array.resize(size);
		return;
	}

	int elementsToAddCount = size - currentSize;
	for (int i = 0; i < elementsToAddCount; i++)
	{
		m_array.push_back(random->getRandomFloat(0, size));
	}
}

bool Sorter::finishedSorting() const
{
	return m_finishedSorting;
}

bool Sorter::isSorting() const
{
	return m_isSorting;
}

void Sorter::waitToFinishWorking()
{
	if (m_sortingThread.joinable())
	{
		m_sortingThread.join();
	}
}

void Sorter::getArrayCopy(std::vector<int>& outCopy)
{
	outCopy.reserve(m_array.size());

	m_arrayMutex.lock();
	std::copy(m_array.begin(), m_array.end(), std::back_inserter(outCopy));
	m_arrayMutex.unlock();
}

SortingAlgorithm Sorter::getAlgorithmName() const
{
	return m_algorithmName;
}

Sorter::Sorter(SortingAlgorithm algorithmName)
	: m_algorithmName(algorithmName)
{}

bool Sorter::isArraySorted() const
{
	for (int i = 0; i < m_array.size() - 1; i++)
	{
		if (m_array[i] > m_array[i + 1])
		{
			return false;
		}
	}

	return true;
}

void Sorter::applyDelay(float currentIterationTime)
{
	float leftTime = m_latency - currentIterationTime;
	if (leftTime > 0.0f)
	{
		std::chrono::nanoseconds delay(static_cast<long long>(leftTime * 1'000'000'000)); //sec to ns
		std::this_thread::sleep_for(delay);
	}
}
