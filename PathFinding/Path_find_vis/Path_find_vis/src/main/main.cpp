#include "pch.h"
#include "../application/application.h"

int main()
{
#if _DEBUG
	std::cout << "Hello there! " << std::endl;
#endif

	{
		PFAV::Application app;
		app.run();
	}

#if _DEBUG
	std::cout << "Press ENTER to close the program" << std::endl;
	std::cin.ignore(100, '\n');
#endif
}