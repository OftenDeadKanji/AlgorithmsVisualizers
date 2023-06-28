#ifndef __BUBBLE_SORTER_HLSL__
#define __BUBBLE_SORTER_HLSL__
#include "sorter.hpp"

class BubbleSorter
	: public Sorter
{
public:
	BubbleSorter();

	void sort() override;
	int getIndex() const override;

private:
	int m_index = 0;
};

#endif