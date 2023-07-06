#include "delaySelector.hpp"
#include <ImGUI/imgui.h>
#include <string>

void DelaySelector::setDelayValueChangeCallback(std::function<void(float delayInSec)> callback)
{
	m_callback_onDelayValueChange = std::move(callback);
}

void DelaySelector::setDelay(float delay)
{
    m_currentDelay = delay;
}

void DelaySelector::updateAndDisplaySelector()
{
    if (ImGui::SliderFloat("##Delay", &m_currentDelay, m_min, m_max, "%.9f", ImGuiSliderFlags_Logarithmic))
    {
        if (m_callback_onDelayValueChange)
        {
            m_callback_onDelayValueChange(m_currentDelay);
        }
    }

    std::string delayUnit;
    if (m_currentDelay >= 0.1f) {
        delayUnit = "s";
    }
    else if (m_currentDelay >= 0.0001f) {
        delayUnit = "ms";
    }
    else if (m_currentDelay >= 0.0000001f){
        delayUnit = "us";
    }
    else {
        delayUnit = "ns";
    }

    std::string delayText = std::to_string(m_currentDelay * (m_currentDelay >= 0.1f ? 1.0f : (m_currentDelay >= 0.0001f ? 1000.0f : (m_currentDelay >= 0.0000001f ? 1000000.0f : 1000000000.0f) ))) + delayUnit;
    ImGui::Text(delayText.c_str());
}
