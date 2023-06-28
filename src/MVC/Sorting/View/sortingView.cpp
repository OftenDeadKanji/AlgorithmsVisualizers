#include "sortingView.hpp"
#include <ImGUI/imgui.h>
#include "../Model/sortingModel.hpp"

SortingView::SortingView(const SortingModel& model, sf::RenderWindow& window)
	: View(model, window)
{
	m_algorithmSelector.setAvailableAlgorithms(SortingModel::getAllAvailableSortingAlgorithms());
	m_arraySizeSelector.setSizeLimit(0, SortingModel::MAX_ARRAY_SIZE);
}

void SortingView::renderSceneToTexture()
{
	std::vector<int> modelArray;
	m_model.getArrayCopy(modelArray);

	if (!modelArray.empty())
	{
		int index = m_model.getIndex();

		const int maxValue = *std::max_element(modelArray.begin(), modelArray.end());

		const float maxHeight = 0.95f * m_newTextureSize.y;
		const float width = (0.95f * m_newTextureSize.x) / modelArray.size();

		sf::RectangleShape arrayElement;
		for (int i = 0; i < modelArray.size(); i++)
		{
			sf::Vector2f size(width, maxHeight * modelArray[i] / maxValue);
			arrayElement.setSize(size);

			sf::Vector2f position(0.0025f * m_newTextureSize.x + i * width, 0.0025f * m_newTextureSize.y + maxHeight - size.y);

			arrayElement.setPosition(position);

			if (m_model.finishedSorting())
			{
				arrayElement.setFillColor(sf::Color::Green);
			}
			else if(index == i)
			{
				arrayElement.setFillColor(sf::Color::Red);
			}
			else
			{
				arrayElement.setFillColor(sf::Color::White);
			}

			m_renderTexture.draw(arrayElement);
		}
	}
}

void SortingView::updateImGuiUIOptionsWindow()
{
	m_algorithmSelector.updateAndDisplaySelector();
	m_arraySizeSelector.updateAndDisplaySelector();
	m_delaySelector.updateAndDisplaySelector();

	if (!m_model.isSorting())
	{
		if (ImGui::Button("Start sorting"))
		{
			if (m_callback_onSortStartButtonClick)
			{
				m_callback_onSortStartButtonClick();
			}
		}
	}
	else
	{
		if (ImGui::Button("Pause sorting"))
		{
			if (m_callback_onSortPauseButtonClick)
			{
				m_callback_onSortPauseButtonClick();
			}
		}
		if (ImGui::Button("Resume sorting"))
		{
			if (m_callback_onSortResumeButtonClick)
			{
				m_callback_onSortResumeButtonClick();
			}
		}
	}
}

void SortingView::setAlgorithmSelectCallback(std::function<void(SortingAlgorithm)> callback)
{
	m_algorithmSelector.setAlgorithmComboListSelectCallback(callback);
}

void SortingView::setDelayValueChangeCallback(std::function<void(float timeInSec)> callback)
{
	m_delaySelector.setDelayValueChangeCallback(callback);
}

void SortingView::setArraySizeChangeCallback(std::function<void(int size)> callback)
{
	m_arraySizeSelector.setArraySizeChangeCallback(callback);
}

void SortingView::setSortStartButtonCallback(std::function<void()> callback)
{
	m_callback_onSortStartButtonClick = std::move(callback);
}

void SortingView::setSortStopButtonCallback(std::function<void()> callback)
{
	m_callback_onSortStopButtonClick = std::move(callback);
}

void SortingView::setSortPauseButtonCallback(std::function<void()> callback)
{
	m_callback_onSortPauseButtonClick = std::move(callback);
}

void SortingView::setSortResumeButtonCallback(std::function<void()> callback)
{
	m_callback_onSortResumeButtonClick = std::move(callback);
}

void SortingView::setDisplayedArraySize(int size)
{
}

void SortingView::setDisplayedDelay(float delay)
{
}
