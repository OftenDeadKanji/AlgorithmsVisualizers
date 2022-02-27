#include "pch.h"
#include "application.h"

namespace PFAV
{
	void Application::run()
	{
		this->init();

		//main [game] loop
		while(!this->controller->getShouldApplicationClose())
		{
			this->processUserInput();
			this->update();
			this->render();
		}
	}

	void Application::init()
	{
		auto resourceManager = Resources::ResourceManager::createResourceManager();
		resourceManager->loadDefaultFont();

		this->controller = std::make_unique<MVC::Controller>();
	}

	void Application::processUserInput()
	{
		this->controller->checkUserInput();
	}

	void Application::update()
	{
		this->controller->modelUpdate();
	}

	void Application::render()
	{
			this->controller->viewRender();
	}
}