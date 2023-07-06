#ifndef __RANDOM_HPP__
#define __RANDOM_HPP__
#include <random>
#include <memory>
#include <algorithm>

class Random
{
public:
	Random(const Random&) = delete;
	Random& operator=(const Random&) = delete;

	static Random* getInstancePtr();

	float getRandomFloat(float min, float max);

	template<typename T>
	void shuffle(std::vector<T>& v);
private:
	Random();

	static std::unique_ptr<Random> s_instance;

	std::uniform_real_distribution<float> m_distribution;
	std::default_random_engine m_randomEngine;
};

#endif

template<typename T>
inline void Random::shuffle(std::vector<T>& v)
{
	std::shuffle(v.begin(), v.end(), m_randomEngine);
}
