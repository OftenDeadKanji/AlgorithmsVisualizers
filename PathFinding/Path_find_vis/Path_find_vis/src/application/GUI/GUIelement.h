#pragma once

namespace PFAV::GUI
{
	class GUIelement
	{
	public:
#pragma region Constructors and Destructor
		GUIelement(std::string name, const sf::IntRect& boundingRect);
		GUIelement(const GUIelement&);
		GUIelement(GUIelement&&) noexcept;

		virtual ~GUIelement() = default;
#pragma endregion
		
#pragma region Operators
		GUIelement& operator=(const GUIelement&);
		GUIelement& operator=(GUIelement&&) noexcept;

		bool operator==(GUIelement& other) const;
#pragma endregion

#pragma region Tree operations
		void addChild(GUIelement*);
		void addChildren(std::vector<std::unique_ptr<GUIelement>>);

		GUIelement* removeChild(const std::string&);
		GUIelement* removeChild(GUIelement*);

		void removeAllChildren();

		GUIelement* findChild(const std::string& name);
		bool hasChild(GUIelement* child);

		GUIelement*& getParent();
		void setParent(GUIelement*);
#pragma endregion

#pragma region Getters, setters
		const std::string& getName() const;
		void setName(std::string);

		const sf::IntRect& getBoundingRect() const;
		virtual void setBoundingRect(const sf::IntRect boundingRect);

		bool isEnabled() const;
		void setEnabled(bool);
#pragma endregion

		virtual void update(const sf::RenderWindow& window, const sf::Mouse&) = 0;

		void draw(sf::RenderWindow& window) const;
		virtual void drawElement(sf::RenderWindow& window) const = 0;

	protected:
		std::string name;
		bool enabled = true;


		//position (in pixels) of upper-left corner
		sf::IntRect boundingRect;

		GUIelement* parent{};
		std::vector<std::unique_ptr<GUIelement>> children;
	};
}
