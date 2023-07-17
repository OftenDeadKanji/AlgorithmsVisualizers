#ifndef __PATHFINDING_VIEW_HPP__
#define __PATHFINDING_VIEW_HPP__

#include "../../Base/View/view.hpp"
#include "../Model/pathFindingModel.hpp"
#include "../../Base/View/algorithmSelector.hpp"
#include "../../Base/View/delaySelector.hpp"
#include "boardSizeSelector.hpp"

class PathFindingView
	: public View
{
public:
	PathFindingView(const PathFindingModel& model, sf::RenderWindow& window);

	void renderSceneToTexture() override;
	void updateImGuiUIOptionsWindow() override;

	void setAlgorithmSelectCallback(std::function<void(PathFindingAlgorithm)> callback);
	void setBoardSizeChangeCallback(std::function<void(std::pair<int, int>)> callback);
	void setDelayChangeCallback(std::function<void(float)> callback);

	void setStartCellAddCallback(std::function<void(std::pair<int, int>)> callback);
	void setEndCellAddCallback(std::function<void(std::pair<int, int>)> callback);
	void setNormalCellAddCallback(std::function<void(std::pair<int, int>)> callback);
	void setObstacleCellAddCallback(std::function<void(std::pair<int, int>)> callback);

	void setStartButtonCallback(std::function<void()> callback);
	void setStopButtonCallback(std::function<void()> callback);
	void setPauseButtonCallback(std::function<void()> callback);
	void setResumeButtonCallback(std::function<void()> callback);

	void setDisplayedBoardSize(const std::pair<int, int>& size);
private:
	const PathFindingModel& m_model = static_cast<const PathFindingModel&>(m_baseModel);
	
	AlgorithmSelector<PathFindingAlgorithm> m_algorithmSelector;
	BoardSizeSelector m_boardSizeSelector;
	DelaySelector m_delaySelector;

	static constexpr int START_CELL_VALUE = 1;
	static constexpr int END_CELL_VALUE = 2;
	static constexpr int NORMAL_CELL_VALUE = 3;
	static constexpr int OBSTACLE_CELL_VALUE = 4;
	int m_chosenCellType = START_CELL_VALUE;

	std::function<void(std::pair<int, int>)> m_callback_onStartCellAdd;
	std::function<void(std::pair<int, int>)> m_callback_onEndCellAdd;
	std::function<void(std::pair<int, int>)> m_callback_onNormalCellAdd;
	std::function<void(std::pair<int, int>)> m_callback_onObstacleCellAdd;

	float zoom = 1.0f;
	float x0 = 0.0f, y0 = 0.0f;
	const float cellSize = 20.0f;
	const float cellBorderSize = 2.0f;

	const sf::Color START_CELL_COLOR = sf::Color::Cyan;
	const sf::Color END_CELL_COLOR = sf::Color::Blue;
	const sf::Color NORMAL_CELL_COLOR = sf::Color::White;
	const sf::Color OBSTACLE_CELL_COLOR = sf::Color::Red;
	const sf::Color PATH_CELL_COLOR = sf::Color::Green;
	const sf::Color SEARCHED_CELL_COLOR = sf::Color::Yellow;

	std::function<void()> m_callback_onStartButtonClick;
	std::function<void()> m_callback_onStopButtonClick;
	std::function<void()> m_callback_onPauseButtonClick;
	std::function<void()> m_callback_onResumeButtonClick;
};

#endif