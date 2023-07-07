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
	void update() override;

	static std::vector<PathFindingAlgorithm> getAllAvailablePathFindingAlgorithms();
	void setAlgorithm(PathFindingAlgorithm algorithm);

	void setStartCell(const std::pair<int, int>& position);
	void setEndCell(const std::pair<int, int>& position);
	void setNormalCell(const std::pair<int, int>& position);
	void setObstacleCell(const std::pair<int, int>& position);

	const std::pair<int, int>& getBoardSize() const;
	void setBoardSize(const std::pair<int, int>& size);
private:
	Board m_board;
	std::unique_ptr<PathFinder> m_pathFinder;
};

#endif