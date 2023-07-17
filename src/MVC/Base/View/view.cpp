#include "view.hpp"
#include <ImGUI/imgui.h>
#include <ImGUI/imgui-SFML.h>

View::View(const Model& model, sf::RenderWindow& window)
	: m_baseModel(model), m_window(window)
{
	m_renderTexture.create(window.getSize());
}

void View::checkEventsAndRender(float deltaTime)
{
	checkSFMLEvents();
	
	render();

	updateImGuiUI(deltaTime);
	
	display();
}

void View::setWindowCloseCallback(std::function<void()> callback)
{
	m_callback_onWindowClose = std::move(callback);
}

void View::checkSFMLEvents()
{
	m_leftMouseButtonClickThisFrame = false;

	sf::Event event;
	while (m_window.pollEvent(event)) 
	{
		ImGui::SFML::ProcessEvent(m_window, event);
		
		switch (event.type)
		{
		case sf::Event::EventType::Closed:
			if (m_callback_onWindowClose)
			{
				m_callback_onWindowClose();
			}
			break;
		case sf::Event::EventType::MouseButtonPressed:
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				m_leftMouseButtonClickThisFrame = true;
			}
			break;
		}
	}
}

void View::updateImGuiUI(float deltaTime)
{
	ImGui::SFML::Update(m_window, sf::seconds(deltaTime));
	ImGui::DockSpaceOverViewport();

	ImGuiWindowClass windowClass;
	windowClass.DockNodeFlagsOverrideSet = ImGuiDockNodeFlags_AutoHideTabBar | 1 << 12;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0.0f, 0.0f));

	ImGui::SetNextWindowClass(&windowClass);
	ImGui::Begin("Viewport", nullptr);
	{
		sf::Vector2u viewportSize = ImGui::GetWindowSize();
		sf::Vector2u currentRenderTextureSize = m_renderTexture.getSize();
		if (viewportSize != currentRenderTextureSize)
		{
			m_resizeTexture = true;
			m_newTextureSize = viewportSize;
		}


		ImGui::Image(m_renderTexture);
	}
	ImGui::End();

	ImGui::PopStyleVar(2);

	ImGui::SetNextWindowClass(&windowClass);
	ImGui::Begin("Hello, world!", nullptr);
	{
		//ImGui::BeginChild("##child", ImVec2(0, 0), true);
		updateImGuiUIOptionsWindow();
		//ImGui::EndChild();
	}
	ImGui::End();
}

void View::render()
{
	if (m_resizeTexture)
	{
		m_renderTexture.create(m_newTextureSize);
	}

	m_renderTexture.clear();
	renderSceneToTexture();
}

void View::display()
{
	m_window.clear();

	ImGui::SFML::Render(m_window);

	m_window.display();
}
