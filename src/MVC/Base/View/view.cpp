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
		}
	}
}

void View::updateImGuiUI(float deltaTime)
{
	ImGui::SFML::Update(m_window, sf::seconds(deltaTime));
	ImGui::DockSpaceOverViewport();

	ImGui::Begin("Viewport", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
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

	ImGui::Begin("Hello, world!", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize );
	{
		updateImGuiUIOptionsWindow();
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
