#include "controller.hpp"
#include "model.hpp"
#include "view.hpp"

Controller::Controller(Model& model, View& view)
	: m_model(model), m_view(view)
{
	m_view.setWindowCloseCallback([&]() {
		m_shouldApplicationRun = false;
		});
}

bool Controller::shouldApplicationRun() const
{
	return m_shouldApplicationRun;
}
