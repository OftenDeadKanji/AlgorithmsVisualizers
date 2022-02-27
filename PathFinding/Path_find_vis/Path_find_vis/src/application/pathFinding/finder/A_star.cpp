#include "pch.h"
#include "A_star.h"

namespace PFAV::Core
{
	A_star::A_star(InputInfo info)
		: Finder(info)
	{}

	void A_star::findPath()
	{
		this->init();

		while(!this->openSet.empty())
		{
			if(!this->inputInfo.continueCondition)
			{
				return;
			}

			float minF = INF;
			size_t nodeNumber = -1;
			for(auto iter : openSet)
			{
				float f = this->g_score[iter] + this->h_score[iter];
				if(f < minF)
				{
					minF = f;
					nodeNumber = iter;
				}
			}

			if(nodeNumber == endNodeNumber)
			{
				break;
			}

			this->openSet.erase(this->openSet.find(nodeNumber));
			this->closedSet.insert(nodeNumber);
			this->boardTilesToUpdate.emplace_back(nodeNumber, Tile::Type::eConsidered);
			this->updateBoard();

			auto nodeNeighbours = this->graph.getNodeNeighbours(nodeNumber);
			for(const auto& neighbour : nodeNeighbours)
			{
				if(!this->inputInfo.continueCondition)
				{
					return;
				}

				if(this->closedSet.find(neighbour->number) != this->closedSet.end())
				{
					continue;
				}

				float g_tmp = g_score[nodeNumber] + this->graph(nodeNumber, neighbour->number);
				bool isTmpBetter = false;
				if(this->openSet.find(neighbour->number) == this->openSet.end())
				{
					this->openSet.insert(neighbour->number);
					isTmpBetter = true;
				}
				else if(g_tmp < g_score[neighbour->number])
				{
					isTmpBetter = true;
				}

				if(isTmpBetter)
				{
					this->previousNode[neighbour->number] = nodeNumber;
					g_score[neighbour->number] = g_tmp;
				}
			}
		}
		if(!this->inputInfo.continueCondition)
		{
			return;
		}

		int previousNodeNumber = -1;
		int currentNode = endNodeNumber;
		std::vector<int> invertedPath;
		do
		{
			previousNodeNumber = this->previousNode[currentNode];
			invertedPath.push_back(previousNodeNumber);
			currentNode = previousNodeNumber;
		} while(previousNodeNumber != startNodeNumber);

		for(int i = invertedPath.size() - 1; i >= 0; --i)
		{
			boardTilesToUpdate.emplace_back(invertedPath[i], Tile::Type::ePath);
		}

		this->updateBoard();
	}

	void A_star::init()
	{
		this->closedSet.clear();

		this->openSet.clear();
		this->openSet.insert(startNodeNumber);

		this->g_score.clear();
		this->g_score.reserve(this->graph.getSize());
		for(size_t i = 0; i < this->graph.getSize(); ++i)
		{
			this->g_score.push_back(INF);
		}
		g_score[this->startNodeNumber] = 0;

		this->h_score.clear();
		this->h_score.reserve(this->graph.getSize());
		for(size_t i = 0; i < this->inputInfo.board.size(); ++i)
		{
			for(size_t j = 0; j < this->inputInfo.board[i].size(); ++j)
			{
				if(!this->inputInfo.continueCondition)
				{
					return;
				}

				if(this->inputInfo.board[i][j].type == Tile::Type::eObstacle)
				{
					h_score.push_back(INF);
					continue;
				}
				int xDiff = this->inputInfo.endPosX - i;
				int yDiff = this->inputInfo.endPosY - j;

				h_score.push_back(std::sqrt(xDiff * xDiff + yDiff * yDiff));
			}
		}

		this->previousNode.clear();
		this->previousNode.reserve(this->graph.getSize());
		for(size_t i = 0; i < this->graph.getSize(); ++i)
		{
			this->previousNode.push_back(-1);
		}
	}

	std::vector<int> A_star::getNodeNeighbours(int nodeNumber)
	{
		std::vector<int> neighbours;

		size_t boardSize = this->inputInfo.board.size();
		int currentNodeNumber = 0;
		for(size_t i = 0; i < boardSize; ++i)
		{
			for(size_t j = 0; j < boardSize; ++j)
			{
				if(currentNodeNumber++ == nodeNumber)
				{
					if(i != 0)
					{
						neighbours.push_back(j + (i - 1) * boardSize);
					}

					if(j != 0)
					{
						neighbours.push_back(j - 1 + i * boardSize);
					}
					if(j != boardSize - 1)
					{
						neighbours.push_back(j + 1 + i * boardSize);
					}
					if(i != boardSize - 1)
					{
						neighbours.push_back(j + (i + 1) * boardSize);
					}
					return neighbours;
				}
			}
		}
		return neighbours;
	}

	void A_star::updateBoard()
	{
		for(auto toUpdate : boardTilesToUpdate)
		{
			for(int i = 0; i < this->inputInfo.board.size(); ++i)
			{
				for(int j = 0; j < this->inputInfo.board[i].size(); ++j)
				{
					if(!this->inputInfo.continueCondition)
					{
						return;
					}

					int nodeNumber = j + i * this->inputInfo.board.size();
					if(toUpdate.first == nodeNumber)
					{
						if(this->inputInfo.board[i][j].type == Tile::Type::eConsidered || this->inputInfo.board[i][j].type == Tile::Type::eEmpty)
						{
							this->inputInfo.board[i][j].type = toUpdate.second;
							std::this_thread::sleep_for(std::chrono::milliseconds(10));
							int a = 10;
						}
					}
				}
			}
		}

		boardTilesToUpdate.clear();
	}
}
