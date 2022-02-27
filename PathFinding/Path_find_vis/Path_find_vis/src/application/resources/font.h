#pragma once
namespace PFAV
{
	namespace Resources
	{
		class Font
			: public sf::Font
		{
		public:
			Font();
			Font(const std::string& fontFilePath);

			void loadFontFromFile(const std::string& fontFilePath);
		};
	}
}