#include "application.hpp"

Application::Application()
	: m_controller(m_model, m_view)
{
	m_timer.reset();
	m_deltaTimeCap = 1.0f / 30.0f;
}

Application::~Application()
{
}

void Application::run()
{
	while (m_controller.shouldApplicationRun())
	{
		updateDeltaTime(m_deltaTimeCap);
		if (m_deltaTime != 0.0f)
		{
			m_model.update();
			m_view.checkEventsAndRender(m_deltaTime);
		}
	}
}

void Application::updateDeltaTime(float deltaTimeCap)
{
	float deltaTime = m_timer.getTimeInSeconds();
	if (deltaTime >= deltaTimeCap)
	{
		m_deltaTime = deltaTime;
		m_timer.reset();

		return;
	}
	
	m_deltaTime = 0.0f;
}
