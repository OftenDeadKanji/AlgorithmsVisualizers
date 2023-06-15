#ifndef __APPLICATION_HPP__
#define __APPLICATION_HPP__
#include <memory>

#include "../MVC/Base/Model/model.hpp"
#include "../MVC/Base/View/view.hpp"
#include "../MVC/Base/Controller/controller.hpp"

#include "applicationState.hpp"

#include "../Utils/Timer/timer.hpp"

class Application
{
public:
	Application();
	~Application();

	void run();
private:
	void updateDeltaTime(float deltaTimeCap = 0.0f);
	void changeApplicationState(ApplicationState newState);

	std::unique_ptr<Model> m_model;
	std::unique_ptr<View> m_view;
	std::unique_ptr<Controller> m_controller;

	Timer m_timer;
	float m_deltaTime;
	float m_deltaTimeCap;

	static constexpr sf::Vector2u DEFAULT_WINDOW_SIZE { 1600, 900 };
	const sf::String DEFAULT_WINDOW_TITLE { L"Algorithms Visualizer - Mateusz Ch³opek 2023" };
	sf::RenderWindow m_window;
};

#endif