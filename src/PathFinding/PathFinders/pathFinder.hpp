#ifndef __PATH_FINDER_HPP
#define __PATH_FINDER_HPP
#include <vector>
#include <thread>
#include <atomic>
#include <mutex>

class Board;

class PathFinder
{
public:
	void start(Board& board);
	virtual void findPath(Board& board) = 0;

private:
	std::thread m_findingThread;
	std::mutex m_boardMutex;

	std::atomic<float> m_latency = 0.0005f; // in s
	std::atomic<bool> m_continueFinding = true; // set to true to make Sorter stop (!= pause) working
	std::atomic<bool> m_stopFinding = false;
	bool m_isFinding = false;
	bool m_finishedFinding = false;
};

#endif