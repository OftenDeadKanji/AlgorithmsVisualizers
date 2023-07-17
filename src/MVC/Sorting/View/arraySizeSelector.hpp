#ifndef __ARRAY_SIZE_SELECTOR__
#define __ARRAY_SIZE_SELECTOR__
#include <functional>

class ArraySizeSelector
{
public:
	void setSizeLimit(int min, int max);
	void setArraySizeChangeCallback(std::function<void(int)> callback);

	void setArraySize(int size);
	int getArraySize() const;

	void updateAndDisplaySelector();
private:
	int m_arraySize = 100;
	int m_min = 2, m_max = 1000;
	std::function<void(int)> m_callback_onArraySizeChange;
};

#endif