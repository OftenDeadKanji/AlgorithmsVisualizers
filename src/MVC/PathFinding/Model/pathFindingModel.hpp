#ifndef __PATHFINDING_MODEL_HPP__
#define __PATHFINDING_MODEL_HPP__

#include "../../Base/Model/model.hpp"
#include <vector>
#include <memory>
#include "../../../PathFinding/pathFindingAlgorithm.hpp"
#include "../../../PathFinding/board.hpp"
#include "../../../PathFinding/PathFinders/pathFinder.hpp"

class PathFindingModel
	: public Model
{
public:
	PathFindingModel();

	void update() override;

	void start();

	static std::vector<PathFindingAlgorithm> getAllAvailablePathFindingAlgorithms();
	void setAlgorithm(PathFindingAlgorithm algorithm);

	void setStartCell(const std::pair<int, int>& position);
	bool isStartCell(const std::pair<int, int>& position) const;

	void setEndCell(const std::pair<int, int>& position);
	bool isEndCell(const std::pair<int, int>& position) const;

	void setNormalCell(const std::pair<int, int>& position);
	//bool isNormalCell(const std::pair<int, int>& position) const;

	void setObstacleCell(const std::pair<int, int>& position);
	//bool isObstacleCell(const std::pair<int, int>& position) const;

	const std::pair<int, int>& getBoardSize() const;
	void setBoardSize(const std::pair<int, int>& size);

	const Board& getBoard() const;

	static constexpr std::pair<int, int> DEFAULT_BOARD_SIZE = { 10, 10 };
private:
	Board m_board;
	std::pair<int, int> m_startCell, m_endCell;

	std::unique_ptr<PathFinder> m_pathFinder;
};

#endif