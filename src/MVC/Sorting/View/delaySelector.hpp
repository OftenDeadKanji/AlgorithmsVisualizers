#ifndef __DELAY_SELECTOR_HPP__
#define __DELAY_SELECTOR_HPP__
#include <functional>

class DelaySelector
{
public:
	void setDelayValueChangeCallback(std::function<void(float delayInSec)> callback);
	
	void setDelay(float delay);

	void updateAndDisplaySelector();
private:
	float m_currentDelay = 0.001f; //1ms
	const float m_min = 0.00000001f, m_max = 0.01f; // [10ns - 10ms]

	std::function<void(float delayInSec)> m_callback_onDelayValueChange;
};

#endif