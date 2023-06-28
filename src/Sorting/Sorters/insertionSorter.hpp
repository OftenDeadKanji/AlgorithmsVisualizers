#ifndef __INSERTION_SORTER_HPP__
#define __INSERTION_SORTER_HPP__
#include "sorter.hpp"

class InsertionSorter
	: public Sorter
{
public:
	InsertionSorter();
	
	void sort() override;
	int getIndex() const override;

private:
	int m_index;
	int m_sortedSize;
};

#endif