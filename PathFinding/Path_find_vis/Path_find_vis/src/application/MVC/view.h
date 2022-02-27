#pragma once
#include "../GUI/button/textButton.h"
#include "../pathFinding/tile/tile.h"

namespace PFAV
{
	namespace MVC
	{
		class Controller;

		class View
		{
		public:
			View(Controller& controller);

			void checkEvents();

			void updateView();
			void render();

		#pragma region Model --> View communication functions
			void passBoard(const std::vector<std::vector<Core::Tile>>& board);
			void passIsModelFindingPath(bool);
			void passModelAlgorithm(Core::Finder::Algorithm currentAlgorithm);
		#pragma endregion

			void renderModelObjects();

			void disableStartButton();
			void disableResetButton();

			void enableStartButton();
			void enableResetButton();

		private:
			enum class TextButtonsNames;
			enum class TextsNames;

			void addButton(TextButtonsNames name, GUI::TextButton&& button);
			void addText(TextsNames name, GUI::Text&& text);

			void initGUI();

			void createButtons();
			void createTexts();

			void createGeneralButtons();
			void createAddTileButtons();
			void createSwitchAlgorithmButtons();
			void createChangeBoardSizeButtons();

			void initTiles();

			std::chrono::time_point<std::chrono::steady_clock> lastFrameEndTimestamp{};
			std::chrono::duration<double> elapsedTime;
			const double FPScapTime = 1.0 / 144.0;

			Controller* controller;

			sf::RenderWindow window;
			sf::Keyboard keyboard;
			sf::Mouse mouse;
			sf::Event lastEvent;

			std::map<TextButtonsNames, GUI::TextButton> textButtons;
			std::map<TextsNames, GUI::Text> texts;

			Core::Tile::Type insertingMode = Core::Tile::Type::eEmpty;

			sf::Vector2f cameraPos{0, 0};
			
			const std::vector<std::vector<Core::Tile>>* board{};
			bool isModelFindingPath = false;

			sf::Vector2f tileSize = {50, 50};
			float thickness = 3.0f;

			sf::RectangleShape tilesShapes[static_cast<int>(Core::Tile::Type::TypesCount)];
			
			bool drawHovered = false;
			sf::Vector2f hoveredPos{0, 0};
			sf::RectangleShape hoveredTile;
		};

	}
}