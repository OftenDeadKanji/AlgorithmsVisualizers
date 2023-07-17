#include "timer.hpp"

void Timer::reset()
{
	m_start = clock::now();
}

float Timer::getTimeInSeconds() const
{
	return duration(clock::now() - m_start).count();
}
