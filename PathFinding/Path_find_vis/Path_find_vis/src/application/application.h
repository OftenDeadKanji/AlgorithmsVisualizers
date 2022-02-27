#pragma once
#include "MVC/controller.h"
#include "resources/resourceManager.h"

namespace PFAV
{
	class Application
	{
	public:
		void run();

	private:
		void init();

		void processUserInput();
		void update();
		void render();

		std::unique_ptr<MVC::Controller> controller;
	};
}