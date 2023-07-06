#include "arraySizeSelector.hpp"
#include <ImGUI/imgui.h>
#include <algorithm>

void ArraySizeSelector::setArraySizeChangeCallback(std::function<void(int)> callback)
{
	m_callback_onArraySizeChange = std::move(callback);
}

void ArraySizeSelector::setSizeLimit(int min, int max)
{
	if (min > max)
	{
		return;
	}

	m_min = std::max(min, 2);
	m_max = max;
}

int ArraySizeSelector::getArraySize() const
{
	return m_arraySize;
}

void ArraySizeSelector::setArraySize(int size)
{
	m_arraySize = size;
}

void ArraySizeSelector::updateAndDisplaySelector()
{
	ImGui::Text("Choose array size:");
	if (ImGui::InputInt("##ArraySelect", &m_arraySize))
	{
		m_arraySize = std::clamp(m_arraySize, m_min, m_max);

		if (m_callback_onArraySizeChange)
		{
			m_callback_onArraySizeChange(m_arraySize);
		}
	}
}
