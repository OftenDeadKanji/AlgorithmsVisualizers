#include "pch.h"
#include "resourceManager.h"

namespace PFAV
{
	namespace Resources
	{
		ResourceManager* ResourceManager::instance = nullptr;
		ResourceManager* ResourceManager::createResourceManager()
		{
			if(instance)
			{
				return instance;
			}

			instance = new ResourceManager();
			return instance;
		}
		ResourceManager* ResourceManager::getInstance()
		{
			return instance;
		}
		void ResourceManager::loadFontFromFile(const std::string& name, const std::string& fontFilePath)
		{
			fonts.emplace(std::make_pair(name, Font(fontFilePath)));
		}
		const Font& ResourceManager::getFont(const std::string& fontName)
		{
			if(fonts.find(fontName) != fonts.end())
			{
				return fonts[fontName];
			}
			
			throw ResourceNotFoundException();
		}
		void ResourceManager::loadDefaultFont()
		{
			this->loadFontFromFile(defaultResourceName, "res/Segan.ttf");
		}
		const Font& ResourceManager::getDefaultFont()
		{
			if(fonts.find(defaultResourceName) != fonts.end())
			{
				return fonts[defaultResourceName];
			}

			throw ResourceNotFoundException();
		}
		ResourceManager::~ResourceManager()
		{
			delete this->instance;
		}
	}
}
