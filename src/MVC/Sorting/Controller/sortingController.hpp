#ifndef __SORTING_CONTROLLER_HPP__
#define __SORTING_CONTROLLER_HPP__

#include "../../Base/Controller/controller.hpp"
#include "../Model/sortingModel.hpp"
#include "../View/sortingView.hpp"

class SortingController
	: public Controller
{
public:
	SortingController(SortingModel& model, SortingView& view);

private:
	SortingModel& m_model = static_cast<SortingModel&>(m_baseModel);
	SortingView& m_view = static_cast<SortingView&>(m_baseView);
};

#endif