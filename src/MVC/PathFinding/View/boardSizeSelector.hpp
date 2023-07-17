#ifndef __BOARD_SIZE_SELECTOR_HPP__
#define __BOARD_SIZE_SELECTOR_HPP__
#include <functional>
#include <utility>

class BoardSizeSelector
{
public:
	void setBoardSizeChangeCallback(std::function<void(std::pair<int, int> size)> callback);

	void setSizeLimit(int min, int max);
	
	void setBoardSize(const std::pair<int, int>& size);
	const std::pair<int, int>& getBoardSize() const;

	void updateAndDisplaySelector();
private:
	std::pair<int, int> m_size{ 2, 2 };
	int m_min = 2, m_max = 10000;

	std::function<void(std::pair<int, int> size)> m_callback_onBoardSizeChange;
};

#endif