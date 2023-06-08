#ifndef __APPLICATION_HPP__
#define __APPLICATION_HPP__

#include "MVC/model.hpp"
#include "MVC/view.hpp"
#include "MVC/controller.hpp"

#include "Utils/Timer/timer.hpp"

class Application
{
public:
	Application();
	~Application();

	void run();
private:
	void updateDeltaTime(float deltaTimeCap = 0.0f);

	Model m_model;
	View m_view;

	Controller m_controller;

	Timer m_timer;
	float m_deltaTime;
	float m_deltaTimeCap;
};

#endif