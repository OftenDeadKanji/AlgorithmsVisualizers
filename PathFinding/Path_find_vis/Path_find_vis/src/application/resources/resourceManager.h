#pragma once
#include "font.h"
namespace PFAV
{
	namespace Resources
	{
		class ResourceNotFoundException
			: public std::exception
		{};

		class ResourceManager
		{
		public:
			static ResourceManager* createResourceManager();
			static ResourceManager* getInstance();

			void loadFontFromFile(const std::string& name, const std::string& fontFilePath);
			const Font& getFont(const std::string& fontName);
			
			void loadDefaultFont();
			const Font& getDefaultFont();

		private:
			static ResourceManager* instance;
			ResourceManager() = default;
			~ResourceManager();

			const std::string defaultResourceName = "default";

			std::unordered_map<std::string, Font> fonts;
		};
	}
}