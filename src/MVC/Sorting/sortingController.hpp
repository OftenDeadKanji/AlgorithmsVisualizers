#ifndef __SORTING_CONTROLLER_HPP__
#define __SORTING_CONTROLLER_HPP__

#include "../controller.hpp"
#include "sortingModel.hpp"
#include "sortingView.hpp"

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