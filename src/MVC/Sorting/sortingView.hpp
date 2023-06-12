#ifndef __SORTING_VIEW_HPP__
#define __SORTING_VIEW_HPP__

#include "../view.hpp"
#include "sortingModel.hpp"

class SortingView
	: public View
{
public:
	SortingView(sf::RenderWindow& window);

	void renderSceneToTexture() override;
	void updateImGuiUIOptionsWindow() override;

private:
};

#endif