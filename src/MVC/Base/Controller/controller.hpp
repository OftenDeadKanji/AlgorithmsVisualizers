#ifndef __CONTROLLER_HPP__
#define __CONTROLLER_HPP__
#include "../../../Application/applicationState.hpp"

class View;
class Model;

class Controller
{
public:
	bool shouldApplicationRun() const;

	bool shouldChangeState() const;
	ApplicationState getNextState() const;
protected:
	Controller(Model& model, View& view, ApplicationState currentState);

	Model& m_baseModel;
	View& m_baseView;

	bool m_shouldApplicationRun = true;

	ApplicationState m_currentState;
	ApplicationState m_nextState;
};

#endif