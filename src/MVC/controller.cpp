#include "controller.hpp"
#include "model.hpp"
#include "view.hpp"

bool Controller::shouldApplicationRun() const
{
	return m_shouldApplicationRun;
}

bool Controller::shouldChangeState() const
{
	return m_nextState != m_currentState;
}

ApplicationState Controller::getNextState() const
{
	return m_nextState;
}

Controller::Controller(Model& model, View& view, ApplicationState currentState)
	: m_baseModel(model), m_baseView(view), m_currentState(currentState), m_nextState(currentState)
{
	m_baseView.setWindowCloseCallback([&]() {
		m_shouldApplicationRun = false;
		});
}