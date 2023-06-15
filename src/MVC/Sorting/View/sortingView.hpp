#ifndef __SORTING_VIEW_HPP__
#define __SORTING_VIEW_HPP__

#include "../../Base/View/view.hpp"
#include "../Model/sortingModel.hpp"

class SortingView
	: public View
{
public:
	SortingView(const SortingModel& model, sf::RenderWindow& window);

	void renderSceneToTexture() override;
	void updateImGuiUIOptionsWindow() override;

private:
	const SortingModel& m_model = static_cast<const SortingModel&>(m_baseModel);
};

#endif