#include "random.hpp"

std::unique_ptr<Random> Random::s_instance(new Random());

Random* Random::getInstancePtr()
{
	return nullptr;
}

float Random::getRandomFloat(float min, float max)
{
	return min + (max - min) * m_distribution(m_randomEngine);
}

Random::Random()
{
	std::random_device rd;
	m_randomEngine = std::default_random_engine(rd());
	m_distribution = std::uniform_real_distribution<float>(0.0f, 1.0f);
}