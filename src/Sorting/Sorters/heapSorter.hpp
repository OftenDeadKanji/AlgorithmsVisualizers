#ifndef __HEAP_SORTER_HPP__
#define __HEAP_SORTER_HPP__
#include "sorter.hpp"

class Timer;

class HeapSorter
	: public Sorter
{
public:
	HeapSorter();

	void sort() override;
	int getIndex() const override;
private:
	void createHeap(Timer& timer);
	void shiftDown(int n, int i, Timer& timer);

	int m_index = 0;
};

#endif