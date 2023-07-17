#include "boardSizeSelector.hpp"
#include <cmath>
#include <algorithm>
#include <ImGUI/imgui.h>

void BoardSizeSelector::setBoardSizeChangeCallback(std::function<void(std::pair<int, int> size)> callback)
{
	m_callback_onBoardSizeChange = std::move(callback);
}

void BoardSizeSelector::setSizeLimit(int min, int max)
{
	if (min > max)
	{
		return;
	}

	m_min = std::max(2, min);
	m_max = max;
}

void BoardSizeSelector::setBoardSize(const std::pair<int, int>& size)
{
	m_size = std::pair<int, int>(
		std::clamp(size.first, m_min, m_max),
		std::clamp(size.second, m_min, m_max)
	);
}

const std::pair<int, int>& BoardSizeSelector::getBoardSize() const
{
	return m_size;
}

void BoardSizeSelector::updateAndDisplaySelector()
{
	ImGui::Text("Choose board size:");

	ImGui::Text("Width");
	ImGui::SameLine();
	if (ImGui::InputInt("##WidthSelect", &m_size.first))
	{
		m_size.first = std::clamp(m_size.first, m_min, m_max);

		if (m_callback_onBoardSizeChange)
		{
			m_callback_onBoardSizeChange(m_size);
		}
	}

	ImGui::Text("Height");
	ImGui::SameLine();
	if (ImGui::InputInt("##HeightSelect", &m_size.second))
	{
		m_size.second = std::clamp(m_size.second, m_min, m_max);

		if (m_callback_onBoardSizeChange)
		{
			m_callback_onBoardSizeChange(m_size);
		}
	}
}
