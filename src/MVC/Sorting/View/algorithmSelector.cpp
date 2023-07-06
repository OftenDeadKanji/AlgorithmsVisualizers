#include "algorithmSelector.hpp"
#include <ImGUI/imgui.h>

void AlgorithmSelector::setAvailableAlgorithms(const std::vector<SortingAlgorithm>& algorithms)
{
	m_availableAlgorithms = algorithms;
	m_availableAlgorithmsNames.reserve(m_availableAlgorithms.size());

	for (auto algorithm : m_availableAlgorithms)
	{
		m_availableAlgorithmsNames.push_back(SortingAlgorithmToString(algorithm));
	}
}

void AlgorithmSelector::updateAndDisplaySelector()
{
	ImGui::Text("Choose algorithm:");

	const char* firstOption = m_availableAlgorithmsNames.empty() ? "No option available" : m_availableAlgorithmsNames[0].c_str();
	if (ImGui::BeginCombo("##AlgorithmsComboList", m_availableAlgorithmsNames[m_currentlyChosenAlgorithm].c_str()))
	{
		for (int i = 0; i < m_availableAlgorithmsNames.size(); i++)
		{
			bool isSelected = m_currentlyChosenAlgorithm == i;
			if (ImGui::Selectable(m_availableAlgorithmsNames[i].c_str(), isSelected))
			{
				m_currentlyChosenAlgorithm = i;

				m_callback_onAlgorithmComboListSelect(m_availableAlgorithms[m_currentlyChosenAlgorithm]);
			}
			if (isSelected)
			{
				ImGui::SetItemDefaultFocus();
			}
		}
		ImGui::EndCombo();
	}
}

void AlgorithmSelector::setAlgorithmComboListSelectCallback(std::function<void(SortingAlgorithm)> callback)
{
	m_callback_onAlgorithmComboListSelect = std::move(callback);
}
