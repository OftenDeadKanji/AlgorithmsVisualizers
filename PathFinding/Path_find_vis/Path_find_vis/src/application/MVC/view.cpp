#include "pch.h"
#include "view.h"
#include "controller.h"

namespace PFAV::MVC
{
	constexpr int StartTile = static_cast<int>(Core::Tile::Type::eStart);
	constexpr int EndTile = static_cast<int>(Core::Tile::Type::eEnd);
	constexpr int EmptyTile = static_cast<int>(Core::Tile::Type::eEmpty);
	constexpr int ObstacleTile = static_cast<int>(Core::Tile::Type::eObstacle);
	constexpr int ConsideredTile = static_cast<int>(Core::Tile::Type::eConsidered);
	constexpr int PathTile = static_cast<int>(Core::Tile::Type::ePath);

	enum class View::TextButtonsNames
	{
		eExit,
		eStart,
		eReset,

		eAddStartTile,
		eAddEndTile,
		eAddEmptyTile,
		eAddObstacle,

		ePreviousAlgorithm,
		eCurrentAlgorithm,
		eNextAlgorithm,

		eDecreaseBoardSize,
		eIncreaseBoardSize
	};

	enum class View::TextsNames
	{
		eCurrentAlgorithm
	};

	View::View(Controller& controller)
		: controller(&controller),
		  window(sf::VideoMode(1600, 900), "Path-finding algorithms visualisation", sf::Style::Titlebar | sf::Style::Close)
	{
		this->initGUI();
		this->initTiles();
	}

	void View::checkEvents()
	{
		while(window.pollEvent(lastEvent))
		{
			switch(lastEvent.type)
			{
			case sf::Event::EventType::Closed:
				this->controller->closeWindowCallback();
				break;
			case sf::Event::EventType::MouseWheelScrolled:
				tileSize.x += lastEvent.mouseWheelScroll.delta;
				tileSize.y += lastEvent.mouseWheelScroll.delta;

				tilesShapes[StartTile].setSize(tileSize);
				tilesShapes[EndTile].setSize(tileSize);
				tilesShapes[EmptyTile].setSize(tileSize);
				tilesShapes[ObstacleTile].setSize(tileSize);
				tilesShapes[PathTile].setSize(tileSize);
				tilesShapes[ConsideredTile].setSize(tileSize);

				hoveredTile.setSize(tileSize);
				break;
			case sf::Event::EventType::MouseButtonPressed:
				if(board)
				{
					auto mousePos = sf::Mouse::getPosition(window);
					if(mousePos.x >= -cameraPos.x && mousePos.x <= (*board).size() * tileSize.x - cameraPos.x
						&&
						mousePos.y >= -cameraPos.y && mousePos.y <= (*board).front().size() * tileSize.y - cameraPos.y)
					{
						for(int i = 0; i < (*board).size(); ++i)
						{
							for(int j = 0; j < (*board)[i].size(); ++j)
							{
								float xPos = i * tileSize.x - cameraPos.x;
								float yPos = j * tileSize.y - cameraPos.y;
								if(mousePos.x >= xPos && mousePos.x <= xPos + tileSize.x
									&&
									mousePos.y >= yPos && mousePos.y <= yPos + tileSize.y)
								{
									this->controller->setTileTypeCallback(i, j, insertingMode);
								}
							}
						}
					}
				}
				break;
			}
		}
	}
	void View::updateView()
	{
		for(auto& textButton : this->textButtons)
		{
			textButton.second.update(window, mouse);
		}

		if(keyboard.isKeyPressed(sf::Keyboard::A))
		{
			cameraPos.x -= 0.01f;
		}
		if(keyboard.isKeyPressed(sf::Keyboard::D))
		{
			cameraPos.x += 0.01f;
		}
		if(keyboard.isKeyPressed(sf::Keyboard::S))
		{
			cameraPos.y += 0.01f;
		}
		if(keyboard.isKeyPressed(sf::Keyboard::W))
		{
			cameraPos.y -= 0.01f;
		}
	}
	void View::render()
	{
		elapsedTime = std::chrono::steady_clock::now() - lastFrameEndTimestamp;
		if(elapsedTime.count() > FPScapTime)
		{
			this->window.clear(sf::Color({12, 122, 222}));

			renderModelObjects();

			for(auto& textButton : this->textButtons)
			{
				textButton.second.draw(window);
			}
			for(auto& text : this->texts)
			{
				text.second.GUIelement::draw(window);
			}

			this->window.display();
			this->lastFrameEndTimestamp = std::chrono::steady_clock::now();
		}
	}

	void View::passBoard(const std::vector<std::vector<Core::Tile>>& board)
	{
		this->board = &board;
	}

	void View::passIsModelFindingPath(bool isFinding)
	{
		this->isModelFindingPath = isFinding;
	}

	void View::passModelAlgorithm(Core::Finder::Algorithm currentAlgorithm)
	{
		switch(currentAlgorithm)
		{
		case PFAV::Core::Finder::Algorithm::eDijkstra:
			this->texts[TextsNames::eCurrentAlgorithm].setText("Dijkstra");
			break;
		case PFAV::Core::Finder::Algorithm::eA_star:
			this->texts[TextsNames::eCurrentAlgorithm].setText("A*");
			break;
		case PFAV::Core::Finder::Algorithm::eBellmanFord:
			this->texts[TextsNames::eCurrentAlgorithm].setText("Bellman-Ford");
			break;
		}
	}

	void View::renderModelObjects()
	{
		if(this->board)
		{
			for(int i = 0; i < (*(this->board)).size(); ++i) // columns
			{
				for(int j = 0; j < (*(this->board))[i].size(); ++j) // rows
				{
					int tile = static_cast<int>((*board)[i][j].type);
					//sf::Vector2f tileSize = {this->tileSize.x + cameraZoom, this->tileSize.x + cameraZoom};
					float xPos = i * tileSize.x - cameraPos.x;
					float yPos = j * tileSize.y - cameraPos.y;

					tilesShapes[tile].setPosition(xPos, yPos);
					auto mousePos = mouse.getPosition(window);
					if(xPos <= mousePos.x && xPos + tileSize.x >= mousePos.x && yPos <= mousePos.y && yPos + tileSize.y >= mousePos.y)
					{
						drawHovered = true;
						hoveredPos = {xPos, yPos};
					}
					window.draw(tilesShapes[tile]);
				}
			}

			if(drawHovered)
			{
				hoveredTile.setPosition(hoveredPos);
				window.draw(hoveredTile);
				drawHovered = false;
			}
		}
	}

	void View::disableStartButton()
	{
		this->textButtons[TextButtonsNames::eStart].setEnabled(false);
	}

	void View::disableResetButton()
	{
		this->textButtons[TextButtonsNames::eReset].setEnabled(false);
	}

	void View::enableStartButton()
	{
		this->textButtons[TextButtonsNames::eStart].setEnabled(true);
	}

	void View::enableResetButton()
	{
		this->textButtons[TextButtonsNames::eReset].setEnabled(true);
	}

	void View::addButton(TextButtonsNames name, GUI::TextButton&& button)
	{
		this->textButtons.insert(std::make_pair(name, std::move(button)));
	}

	void View::addText(TextsNames name, GUI::Text&& text)
	{
		this->texts.insert(std::make_pair(name, std::move(text)));
	}

	void View::initGUI()
	{
		this->createButtons();
		this->createTexts();
	}

	void View::createButtons()
	{
		this->createGeneralButtons();
		this->createAddTileButtons();
		this->createSwitchAlgorithmButtons();
		this->createChangeBoardSizeButtons();
	}

	void View::createTexts()
	{
		this->addText(TextsNames::eCurrentAlgorithm, GUI::Text("currAlg", {1430, 550, 0, 0}, "?"));
	}

	void View::createGeneralButtons()
	{
		GUI::TextButton exitButton("exit", {1500, 800, 0, 0}, "Exit");
		exitButton.setOnClickCallback(
			[this]()
			{
				this->controller->exitButtonCallback();
			}
		);
		this->addButton(TextButtonsNames::eExit, std::move(exitButton));

		GUI::TextButton	startButton("start", {1500, 50, 0, 0}, "Start");
		startButton.setOnClickCallback(
			[this]()
			{
				this->controller->startButtonCallback();
			}
		);
		this->addButton(TextButtonsNames::eStart, std::move(startButton));

		GUI::TextButton	resetButton("reset", {1500, 100, 0, 0}, "Reset");
		resetButton.setOnClickCallback(
			[this]()
			{
				this->controller->resetButtonCallback();
			}
		);
		resetButton.setEnabled(false);
		this->addButton(TextButtonsNames::eReset, std::move(resetButton));
	}

	void View::createAddTileButtons()
	{
		GUI::TextButton	addStartTileButton("addStartTile", {1200, 200, 0, 0}, "Add \"Start\" tile");
		addStartTileButton.setOnClickCallback(
			[this]()
			{
				this->insertingMode = Core::Tile::Type::eStart;
				hoveredTile.setFillColor(sf::Color::Green);
			}
		);
		this->addButton(TextButtonsNames::eAddStartTile, std::move(addStartTileButton));

		GUI::TextButton	addEndTileButton("addEndTile", {1200, 250, 0, 0}, "Add \"End\" tile");
		addEndTileButton.setOnClickCallback(
			[this]()
			{
				this->insertingMode = Core::Tile::Type::eEnd;
				hoveredTile.setFillColor(sf::Color::Blue);
			}
		);
		this->addButton(TextButtonsNames::eAddEndTile, std::move(addEndTileButton));

		GUI::TextButton	addEmptyTileButton("addEmptyTile", {1200, 300, 0, 0}, "Add \"Empty\" tile");
		addEmptyTileButton.setOnClickCallback(
			[this]()
			{
				this->insertingMode = Core::Tile::Type::eEmpty;
				hoveredTile.setFillColor(sf::Color::White);
			}
		);
		this->addButton(TextButtonsNames::eAddEmptyTile, std::move(addEmptyTileButton));

		GUI::TextButton	addObstacleTileButton("addObstacleTile", {1200, 350, 0, 0}, "Add \"Obstacle\" tile");
		addObstacleTileButton.setOnClickCallback(
			[this]()
			{
				this->insertingMode = Core::Tile::Type::eObstacle;
				hoveredTile.setFillColor(sf::Color::Red);
			}
		);
		this->addButton(TextButtonsNames::eAddObstacle, std::move(addObstacleTileButton));
	}

	void View::createSwitchAlgorithmButtons()
	{
		GUI::TextButton	previousAlgorithm("prevAlg", {1400, 500, 0, 0}, "<");
		previousAlgorithm.setOnClickCallback(
			[this]()
			{
				this->controller->previousAlgorithmButtonCallback();
			}
		);
		this->addButton(TextButtonsNames::ePreviousAlgorithm, std::move(previousAlgorithm));

		GUI::TextButton	nextAlgorithm("nextAlg", {1500, 500, 0, 0}, ">");
		nextAlgorithm.setOnClickCallback(
			[this]()
			{
				this->controller->nextAlgorithmButtonCallback();
			}
		);
		this->addButton(TextButtonsNames::eNextAlgorithm, std::move(nextAlgorithm));
	}

	void View::createChangeBoardSizeButtons()
	{
		GUI::TextButton	decreaseBoardSize("decSize", {1100, 500, 0, 0}, "-10");
		decreaseBoardSize.setOnClickCallback(
			[this]()
			{
				this->controller->decreaseBoardSizeButtonCallback();
			}
		);
		this->addButton(TextButtonsNames::eDecreaseBoardSize, std::move(decreaseBoardSize));

		GUI::TextButton	increaseBoardSize("incSize", {1200, 500, 0, 0}, "+10");
		increaseBoardSize.setOnClickCallback(
			[this]()
			{
				this->controller->increaseBoardSizeButtonCallback();
			}
		);
		this->addButton(TextButtonsNames::eIncreaseBoardSize, std::move(increaseBoardSize));
	}

	void View::initTiles()
	{
		for (auto& tilesShape : tilesShapes)
		{
			tilesShape.setSize(tileSize);
			tilesShape.setOutlineColor(sf::Color::Black);
			tilesShape.setOutlineThickness(-1);
		}
		tilesShapes[StartTile].setFillColor(sf::Color::Green);
		tilesShapes[EndTile].setFillColor(sf::Color::Blue);
		tilesShapes[EmptyTile].setFillColor(sf::Color::White);
		tilesShapes[ObstacleTile].setFillColor(sf::Color::Red);
		tilesShapes[PathTile].setFillColor(sf::Color::Yellow);
		tilesShapes[ConsideredTile].setFillColor(sf::Color(255, 127, 39));

		hoveredTile.setSize(tileSize);
		hoveredTile.setFillColor(sf::Color::White);
		hoveredTile.setOutlineColor(sf::Color(200, 200, 200));
		hoveredTile.setOutlineThickness(-1);
	}
}
