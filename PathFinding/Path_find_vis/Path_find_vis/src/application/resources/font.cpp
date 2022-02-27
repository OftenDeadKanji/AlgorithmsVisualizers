#include "pch.h"
#include "font.h"

namespace PFAV
{
	namespace Resources
	{
		Font::Font() : sf::Font()
		{}

		Font::Font(const std::string& fontFilePath) : sf::Font()
		{
			this->loadFromFile(fontFilePath);
		}

		void Font::loadFontFromFile(const std::string& fontFilePath)
		{
			this->loadFromFile(fontFilePath);
		}
	}
}