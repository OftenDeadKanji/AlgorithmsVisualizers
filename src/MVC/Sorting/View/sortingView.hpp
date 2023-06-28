#ifndef __SORTING_VIEW_HPP__
#define __SORTING_VIEW_HPP__

#include "../../Base/View/view.hpp"
#include "algorithmSelector.hpp"

class SortingView
	: public View
{
public:
	SortingView(sf::RenderWindow& window);

	void renderSceneToTexture() override;
	void updateImGuiUIOptionsWindow() override;

	void setAlgorithmComboListSelectCallback(std::function<void(SortingAlgorithm)> callback);

private:
    const SortingModel& m_model = static_cast<const SortingModel&>(m_baseModel);

	AlgorithmSelector m_algorithmSelector;
};

#endif

	