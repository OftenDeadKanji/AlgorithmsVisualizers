#include <ImGUI/imgui.h>
#include <ImGUI/imgui-SFML.h>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(640, 480)), "ImGui + SFML = <3");
    
    ImGui::SFML::Init(window);
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
   
    sf::RenderTexture renderTexture;
    renderTexture.create(sf::Vector2u(640, 480));

    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(window, event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::DockSpaceOverViewport();
        
        ImGui::Begin("Viewport", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
        sf::Vector2u viewportSize = ImGui::GetWindowSize();
        sf::Vector2u currentRenderTextureSize = renderTexture.getSize();
        if (viewportSize != currentRenderTextureSize)
        {
            renderTexture.create(viewportSize);
        }
        
        renderTexture.clear();
        renderTexture.draw(shape);
        ImGui::Image(renderTexture);
        ImGui::End();

        ImGui::Begin("Hello, world!", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
        ImGui::Button("Look at this pretty button");
        ImGui::End();


        window.clear();
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();

    return 0;
}