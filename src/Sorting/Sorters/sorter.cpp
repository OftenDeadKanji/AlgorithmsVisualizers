#include "sorter.hpp"
#include "../../Utils/Random/random.hpp"

void Sorter::sort()
{
	
}

void Sorter::pause()
{
	m_continueSorting.store(false);
}

void Sorter::resume()
{
	m_continueSorting.store(true);
}

void Sorter::setLatency(float latency)
{
	m_latency.store(latency);
}

void Sorter::setArraySize(int size)
{
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
	return false;
}

void Sorter::getArrayCopy(std::vector<int>& outCopy)
{
	outCopy.reserve(m_array.size());

	m_arrayMutex.lock();
	std::copy(m_array.begin(), m_array.end(), outCopy.begin());
	m_arrayMutex.unlock();
}
