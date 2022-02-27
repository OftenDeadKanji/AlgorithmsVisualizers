#include "pch.h"
#include "GUIelement.h"

namespace PFAV::GUI
{
	GUIelement::GUIelement(std::string name, const sf::IntRect& boundingRect)
		:name(std::move(name)), boundingRect(boundingRect)
	{}

	GUIelement::GUIelement(const GUIelement& other)
		: name(other.name), boundingRect(other.boundingRect), parent(other.parent)
	{


	}

	GUIelement::GUIelement(GUIelement&& other) noexcept
		: name(std::move(other.name)), boundingRect(other.boundingRect)
	{
		this->parent = other.parent;
		other.parent = nullptr;

		this->children.swap(other.children);
	}

	GUIelement& GUIelement::operator=(const GUIelement& other)
	{
		if(this != &other)
		{
			this->name = other.name;
			this->boundingRect = other.boundingRect;
			this->parent = other.parent;
		}
		return *this;
	}

	GUIelement& GUIelement::operator=(GUIelement&& other) noexcept
	{
		if(this == &other)
		{
			this->name = std::move(other.name);
			this->boundingRect = other.boundingRect;

			this->parent = other.parent;
			other.parent = nullptr;

			this->children.swap(other.children);
		}
		return *this;
	}

	bool GUIelement::operator==(GUIelement& other) const
	{
		return this->name == other.name;
	}

	void GUIelement::addChild(GUIelement* newChild)
	{
		//children.push_back(std::make_unique<GUIelement>(*newChild));
	}

	void GUIelement::addChildren(std::vector<std::unique_ptr<GUIelement>> v)
	{
		//children.insert(children.end(), v.begin(), v.end());
	}

	GUIelement* GUIelement::removeChild(const std::string& name)
	{
		for(auto iter = children.begin(); iter != children.end(); ++iter)
		{
			if((*iter)->name == name)
			{
				auto& tmp = *iter;
				children.erase(iter);
				return tmp.release();
			}
		}
		return nullptr;
	}
	GUIelement* GUIelement::removeChild(GUIelement* child)
	{
		for(auto iter = children.begin(); iter != children.end(); ++iter)
		{
			if(iter->get() == child)
			{
				auto& tmp = *iter;
				children.erase(iter);
				return tmp.release();
			}
		}
		return nullptr;
	}

	void GUIelement::removeAllChildren()
	{
		this->children.clear();
	}

	GUIelement* GUIelement::findChild(const std::string& name)
	{
		for(auto iter = children.begin(); iter != children.end(); ++iter)
		{
			if((*iter)->name == name)
			{
				return iter->get();
			}
		}
		return nullptr;
	}

	bool GUIelement::hasChild(GUIelement* child)
	{
		for(auto& childPtr : children)
		{
			if(*childPtr == *child)
				return true;
		}
		return false;
	}

	GUIelement*& GUIelement::getParent()
	{
		return this->parent;
	}

	void GUIelement::setParent(GUIelement* newParent)
	{
		this->parent = newParent;
	}
	const std::string& GUIelement::getName() const
	{
		return this->name;
	}
	void GUIelement::setName(std::string newName)
	{
		this->name = std::move(newName);
	}

	const sf::IntRect& GUIelement::getBoundingRect() const
	{
		return this->boundingRect;
	}

	void GUIelement::setBoundingRect(const sf::IntRect boundingRect)
	{
		this->boundingRect = boundingRect;
	}

	bool GUIelement::isEnabled() const
	{
		return this->enabled;
	}

	void GUIelement::setEnabled(bool enabled)
	{
		this->enabled = enabled;
	}

	void GUIelement::draw(sf::RenderWindow& window) const
	{
		this->drawElement(window);
		for(auto& child : children)
		{
			(*child).draw(window);
		}
	}
}
