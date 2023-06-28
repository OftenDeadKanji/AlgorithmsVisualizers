#ifndef __SORTING_VIEW_HPP__
#define __SORTING_VIEW_HPP__

#include "../../Base/View/view.hpp"
#include "../Model/sortingModel.hpp"
#include "algorithmSelector.hpp"
#include "arraySizeSelector.hpp"
#include "delaySelector.hpp"

class SortingView
	: public View
{
public:
	SortingView(const SortingModel& model, sf::RenderWindow& window);

	void renderSceneToTexture() override;
	void updateImGuiUIOptionsWindow() override;

	void setAlgorithmSelectCallback(std::function<void(SortingAlgorithm)> callback);
	void setDelayValueChangeCallback(std::function<void(float timeInSec)> callback);
	void setArraySizeChangeCallback(std::function<void(int size)> callback);
	void setSortStartButtonCallback(std::function<void()> callback);
	void setSortStopButtonCallback(std::function<void()> callback);
	void setSortPauseButtonCallback(std::function<void()> callback);
	void setSortResumeButtonCallback(std::function<void()> callback);

	void setDisplayedArraySize(int size);
	void setDisplayedDelay(float delay);
private:
    const SortingModel& m_model = static_cast<const SortingModel&>(m_baseModel);

	AlgorithmSelector m_algorithmSelector;
	ArraySizeSelector m_arraySizeSelector;
	DelaySelector m_delaySelector;
	std::function<void()> m_callback_onSortStartButtonClick;
	std::function<void()> m_callback_onSortStopButtonClick;
	std::function<void()> m_callback_onSortPauseButtonClick;
	std::function<void()> m_callback_onSortResumeButtonClick;
};

#endif
