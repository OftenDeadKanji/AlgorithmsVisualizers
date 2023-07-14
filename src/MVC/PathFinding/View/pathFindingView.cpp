#include "pathFindingView.hpp"
#include <ImGUI/imgui.h>

PathFindingView::PathFindingView(const PathFindingModel& model, sf::RenderWindow& window)
	: View(model, window)
{
	m_algorithmSelector.setAvailableAlgorithms(PathFindingModel::getAllAvailablePathFindingAlgorithms());
}

void PathFindingView::renderSceneToTexture()
{
	const auto& board = m_model.getBoard();
	auto boardSize = m_model.getBoardSize();

	sf::RectangleShape cell;
	cell.setSize(sf::Vector2f(cellSize - cellBorderSize, cellSize - cellBorderSize));
	for (int i = 0; i < boardSize.first; i++)
	{
		for (int j = 0; j < boardSize.second; j++)
		{
			cell.setPosition(sf::Vector2f(x0 + cellSize * i + cellBorderSize, y0 + cellSize * j + cellBorderSize));

			auto pos = std::make_pair(i, j);

			sf::Color color =
				board.isObstacleCell(pos) ? OBSTACLE_CELL_COLOR :
				board.isStartCell(pos) ? START_CELL_COLOR :
				board.isEndCell(pos) ? END_CELL_COLOR :
				board.isVisitedCell(pos) ? SEARCHED_CELL_COLOR :
				board.isPathCell(pos) ? PATH_CELL_COLOR :
				NORMAL_CELL_COLOR;

			cell.setFillColor(color);

			m_renderTexture.draw(cell);
		}
	}
}

void PathFindingView::updateImGuiUIOptionsWindow()
{
	m_algorithmSelector.updateAndDisplaySelector();
	m_boardSizeSelector.updateAndDisplaySelector();

	ImGui::RadioButton("StartCell", &m_chosenCellType, START_CELL_VALUE);
	ImGui::RadioButton("EndCell", &m_chosenCellType, END_CELL_VALUE);
	ImGui::RadioButton("NormalCell", &m_chosenCellType, NORMAL_CELL_VALUE);
	ImGui::RadioButton("ObstacleCell", &m_chosenCellType, OBSTACLE_CELL_VALUE);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		auto pos = sf::Mouse::getPosition(m_window);

		if (pos.x >= 0 && pos.x < m_newTextureSize.x && pos.y >= 0 && pos.y < m_newTextureSize.y)
		{
			auto relPos = pos - sf::Vector2i(x0, y0);

			auto poss = std::make_pair(static_cast<int>(relPos.x / cellSize), static_cast<int>(relPos.y / cellSize));

			switch (m_chosenCellType)
			{
			case START_CELL_VALUE:
				m_callback_onStartCellAdd(poss);
				break;
			case END_CELL_VALUE:
				m_callback_onEndCellAdd(poss);
				break;
			case NORMAL_CELL_VALUE:
				m_callback_onNormalCellAdd(poss);
				break;
			case OBSTACLE_CELL_VALUE:
				m_callback_onObstacleCellAdd(poss);
				break;
			}
		}
	}

	if (ImGui::Button("Start"))
	{
		if (m_callback_onStartButtonClick)
		{
			m_callback_onStartButtonClick();
		}
	}
}

void PathFindingView::setAlgorithmSelectCallback(std::function<void(PathFindingAlgorithm)> callback)
{
	m_algorithmSelector.setAlgorithmComboListSelectCallback(callback);
}

void PathFindingView::setBoardSizeChangeCallback(std::function<void(std::pair<int, int>)> callback)
{
	m_boardSizeSelector.setBoardSizeChangeCallback(callback);
}

void PathFindingView::setStartCellAddCallback(std::function<void(std::pair<int, int>)> callback)
{
	m_callback_onStartCellAdd = std::move(callback);
}

void PathFindingView::setEndCellAddCallback(std::function<void(std::pair<int, int>)> callback)
{
	m_callback_onEndCellAdd = std::move(callback);
}

void PathFindingView::setNormalCellAddCallback(std::function<void(std::pair<int, int>)> callback)
{
	m_callback_onNormalCellAdd = std::move(callback);
}

void PathFindingView::setObstacleCellAddCallback(std::function<void(std::pair<int, int>)> callback)
{
	m_callback_onObstacleCellAdd = std::move(callback);
}

void PathFindingView::setStartButtonCallback(std::function<void()> callback)
{
	m_callback_onStartButtonClick = std::move(callback);
}

void PathFindingView::setDisplayedBoardSize(const std::pair<int, int>& size)
{
	m_boardSizeSelector.setBoardSize(size);
}
