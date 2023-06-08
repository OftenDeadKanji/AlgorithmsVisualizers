#include <chrono>

class Timer
{
public:
	void reset();
	float getTimeInSeconds() const;

private:
	using clock = std::chrono::high_resolution_clock;
	using duration = std::chrono::duration<float>;

	clock::time_point m_start;
};