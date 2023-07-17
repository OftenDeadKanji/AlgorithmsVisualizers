#ifndef __BOARD_HPP__
#define __BOARD_HPP__
#include <vector>
#include <utility>
#include <limits>

class Board
{
public:
	enum class CellType
	{
		Normal,
		Obstacle,
		Start,
		End,

		Searched,
		Path
	};
	using Weight = double;
	static constexpr Weight NormalWeight = 1.0;
	static constexpr Weight DiagonalWeight = 1.42;
	static constexpr Weight ObstacleWeight = std::numeric_limits<double>::max();

	Weight& operator()(const std::pair<int, int>& from, const std::pair<int, int>& to);
	const Weight& operator()(const std::pair<int, int>& from, const std::pair<int, int>& to) const;

	Weight& operator()(int xFrom, int yFrom, int xTo, int yTo);
	const Weight& operator()(int xFrom, int yFrom, int xTo, int yTo) const;

	void setSize(const std::pair<int, int>& size);
	std::pair<int, int> getSize() const;

	void setNormalCell(const std::pair<int, int>& position);
	void setNormalCell(int x, int y);
	bool isNormalCell(const std::pair<int, int>& position) const;
	bool isNormalCell(int x, int y) const;

	void setObstacleCell(const std::pair<int, int>& position);
	void setObstacleCell(int x, int y);
	bool isObstacleCell(const std::pair<int, int>& position) const;
	bool isObstacleCell(int x, int y) const;

	void setStartCell(const std::pair<int, int>& position);
	void setStartCell(int x, int y);
	bool isStartCell(const std::pair<int, int>& position) const;
	bool isStartCell(int x, int y) const;
	std::pair<int, int> getStartPosition() const;
	int getStartFlatPosition() const;

	void setEndCell(const std::pair<int, int>& position);
	void setEndCell(int x, int y);
	bool isEndCell(const std::pair<int, int>& position) const;
	bool isEndCell(int x, int y) const;
	std::pair<int, int> getEndtPosition() const;
	int getEndFlatPosition() const;

	void setVisitedCell(const std::pair<int, int>& position);
	void setVisitedCell(int x, int y);
	bool isVisitedCell(const std::pair<int, int>& position) const;
	bool isVisitedCell(int x, int y) const;

	void setPathCell(const std::pair<int, int>& position);
	void setPathCell(int x, int y);
	bool isPathCell(const std::pair<int, int>& position) const;
	bool isPathCell(int x, int y) const;

	std::vector<std::pair<int, int>> getNeighboursPositions(std::pair<int, int> cellPosition) const;
	std::vector<std::pair<int, int>> getNeighboursPositions(int x, int y) const;

	int getFlatPosition(const std::pair<int, int>& position) const;
	int getFlatPosition(int x, int y) const;

	std::vector<int> getNeighboursFlatPositions(std::pair<int, int> cellPosition) const;
	std::vector<int> getNeighboursFlatPositions(int x, int y) const;

	void initWeights();
	void semiClear(); // clears Searched and Path
private:
	std::pair<int, int> m_size;
	std::vector<std::vector<CellType>> m_cells;
	std::vector<std::vector<Weight>> m_weightGraph;

	std::pair<int, int> m_start{-1, -1}, m_end{ -1, -1 };
};

#endif