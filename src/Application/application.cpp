#include "application.hpp"
#include "../MVC/Menu/menuController.hpp"
#include "../MVC/Sorting/sortingController.hpp"
#include "../MVC/PathFinding/pathFindingController.hpp"
#include <ImGUI/imgui.h>
#include <ImGUI/imgui-SFML.h>

Application::Application()
{
	m_window.create(sf::VideoMode(this->DEFAULT_WINDOW_SIZE), this->DEFAULT_WINDOW_TITLE);

	ImGui::SFML::Init(m_window);
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard | ImGuiConfigFlags_DockingEnable;

	changeApplicationState(ApplicationState::Menu);

	m_timer.reset();
	m_deltaTimeCap = 1.0f / 30.0f;
}

Application::~Application()
{
	ImGui::SFML::Shutdown();
	m_window.close();
}

void Application::run()
{
	while (m_controller->shouldApplicationRun())
	{
		updateDeltaTime(m_deltaTimeCap);
		if (m_deltaTime != 0.0f)
		{
			m_model->update();
			m_view->checkEventsAndRender(m_deltaTime);

			if (m_controller->shouldChangeState())
			{
				changeApplicationState(m_controller->getNextState());
			}
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

void Application::changeApplicationState(ApplicationState newState)
{
	switch (newState)
	{
	case ApplicationState::Menu:
		m_model = std::make_unique<MenuModel>();
		m_view = std::make_unique<MenuView>(m_window);
		m_controller = std::make_unique<MenuController>(static_cast<MenuModel&>(*m_model), static_cast<MenuView&>(*m_view));

		break;
	case ApplicationState::Sorting:
		m_model = std::make_unique<SortingModel>();
		m_view = std::make_unique<SortingView>(m_window);
		m_controller = std::make_unique<SortingController>(static_cast<SortingModel&>(*m_model), static_cast<SortingView&>(*m_view));

		break;
	case ApplicationState::PathFinding:
		m_model = std::make_unique<PathFindingModel>();
		m_view = std::make_unique<PathFindingView>(m_window);
		m_controller = std::make_unique<PathFindingController>(static_cast<PathFindingModel&>(*m_model), static_cast<PathFindingView&>(*m_view));

		break;
	}
}
