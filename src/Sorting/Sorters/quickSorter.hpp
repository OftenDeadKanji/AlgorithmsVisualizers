#ifndef __QUICK_SORTER_HPP__
#define __QUICK_SORTER_HPP__
#include "sorter.hpp"

class Timer;

class QuickSorter
	: public Sorter
{
public:
	QuickSorter();

	void sort() override;

	int getIndex() const override;

private:
	void quicksort(int l, int r, Timer& timer);
	int divide(int l, int r, Timer& timer);

	int m_index;
};

#endif