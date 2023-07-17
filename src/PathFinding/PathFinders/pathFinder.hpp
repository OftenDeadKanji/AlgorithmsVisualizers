#ifndef __PATH_FINDER_HPP
#define __PATH_FINDER_HPP
#include <vector>
#include <thread>
#include <atomic>
#include <mutex>
#include "../pathFindingAlgorithm.hpp"

class Board;

class PathFinder
{
public:
	PathFindingAlgorithm getAlgorithm() const;

	void start(Board& board);
	void stop();
	void pause();
	void resume();

	virtual void findPath(Board& board) = 0;

	void setDelay(float delay);
	float getDelay() const;

	bool finishedFinding() const;
	bool isFinding() const;
	void waitToFinishWorking();

protected:
	PathFinder(PathFindingAlgorithm algorithm);

	std::thread m_findingThread;
	std::mutex m_boardMutex;

	PathFindingAlgorithm m_algorithm;

	std::atomic<float> m_latency = 0.0005f; // in s
	std::atomic<bool> m_continueFinding = true; // set to true to make Sorter stop (!= pause) working
	std::atomic<bool> m_stopFinding = false;
	
	bool m_isFinding = false;
	bool m_finishedFinding = false;


};

#endif