#include "view.hpp"
#include <ImGUI/imgui.h>
#include <ImGUI/imgui-SFML.h>

View::View()
{
	m_window.create(sf::VideoMode(this->DEFAULT_WINDOW_SIZE), this->DEFAULT_WINDOW_TITLE);
	m_renderTexture.create(this->DEFAULT_WINDOW_SIZE);

	ImGui::SFML::Init(m_window);
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard | ImGuiConfigFlags_DockingEnable;
}

View::~View()
{
	ImGui::SFML::Shutdown();
	m_window.close();
}

void View::checkEventsAndRender(float deltaTime)
{
	checkSFMLEvents();
	
	renderSceneToTexture();

	updateImGuiUI(deltaTime);
	
	render();
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

	ImGui::Begin("Hello, world!", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
	{
		ImGui::LabelText("Delta Time", "Delta Time: %.3fms", deltaTime * 1000.0f);
	}
	ImGui::End();
}

void View::renderSceneToTexture()
{
	if (m_resizeTexture)
	{
		m_renderTexture.create(m_newTextureSize);
	}

	m_renderTexture.clear();

}

void View::render()
{
	m_window.clear();

	ImGui::SFML::Render(m_window);

	m_window.display();
}
