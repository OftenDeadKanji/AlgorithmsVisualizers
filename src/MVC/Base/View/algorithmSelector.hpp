#ifndef __ALGORITHM_SELECTOR_HPP__
#define __ALGORITHM_SELECTOR_HPP__
#include <functional>
#include <vector>
#include <string>
#include <ImGUI/imgui.h>

template<typename T>
class AlgorithmSelector
{
public:
	void setAvailableAlgorithms(const std::vector<T>& algorithms);
	void updateAndDisplaySelector();
	void setAlgorithmComboListSelectCallback(std::function<void(T)> callback);
private:
	std::vector<T> m_availableAlgorithms;
	std::vector<std::string> m_availableAlgorithmsNames;
	size_t m_currentlyChosenAlgorithm = 0;

	std::function<void(T)> m_callback_onAlgorithmComboListSelect;
};

template<typename T>
inline void AlgorithmSelector<T>::setAvailableAlgorithms(const std::vector<T>& algorithms)
{
	m_availableAlgorithms = algorithms;
	m_availableAlgorithmsNames.reserve(m_availableAlgorithms.size());

	for (auto algorithm : m_availableAlgorithms)
	{
		m_availableAlgorithmsNames.push_back(SortingAlgorithmToString(algorithm));
	}
}

template<typename T>
void AlgorithmSelector<T>::updateAndDisplaySelector()
{
	ImGui::Text("Choose algorithm:");

	const char* firstOption = m_availableAlgorithmsNames.empty() ? "No option available" : m_availableAlgorithmsNames[m_currentlyChosenAlgorithm].c_str();
	if (ImGui::BeginCombo("##AlgorithmsComboList", firstOption))
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

template<typename T>
void AlgorithmSelector<T>::setAlgorithmComboListSelectCallback(std::function<void(T)> callback)
{
	m_callback_onAlgorithmComboListSelect = std::move(callback);
}

#endif