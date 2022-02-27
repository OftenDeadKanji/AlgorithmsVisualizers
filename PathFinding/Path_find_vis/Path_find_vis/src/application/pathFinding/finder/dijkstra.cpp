#include "pch.h"
#include "dijkstra.h"

namespace PFAV::Core
{
	Dijkstra::Dijkstra(InputInfo info)
		: Finder(info)
	{}

	void Dijkstra::findPath()
	{
		this->init();

		while(!Q.empty())
		{
			if(!inputInfo.continueCondition)
			{
				return;
			}

			int u = Q.top();
			Q.pop();

			std::vector<int> u_neighbours;
			u_neighbours.reserve(9);
			for(int i = 0; i < graph.getSize(); ++i)
			{
				if(i == u)
				{
					continue;
				}

				if(graph(u, i) != INF)
				{
					u_neighbours.push_back(i);
				}
			}

			for(auto v : u_neighbours)
			{
				if(d[u] + graph(u, v) < d[v])
				{
					d[v] = d[u] + graph(u, v);
					previous[v] = u;
				}
			}

			this->boardTilesToUpdate.push_back(std::make_pair(u, Tile::Type::eConsidered));
			this->updateBoard();

			if(u == endNodeNumber)
			{
				break;
			}

			Q_copy.swap(Q);
			while(!Q_copy.empty())
			{
				auto node = Q_copy.top();
				Q_copy.pop();

				Q.push(node);
			}
		}
		int previousNode = -1;
		int currentNode = endNodeNumber;
		std::vector<int> inversedPath;
		do
		{
			previousNode = previous[currentNode];
			inversedPath.push_back(previousNode);
			currentNode = previousNode;
		} while(previousNode != startNodeNumber);

		for(int i = inversedPath.size() - 1; i >= 0; --i)
		{
			boardTilesToUpdate.push_back(std::make_pair(inversedPath[i], Tile::Type::ePath));
		}

		this->updateBoard();

		while(!Q.empty())
		{
			Q.pop();
		}
		while(!Q_copy.empty())
		{
			Q_copy.pop();
		}
	}

	void Dijkstra::init()
	{
		d.reserve(this->graph.getSize());
		for(size_t i = 0; i < this->graph.getSize(); ++i)
		{
			d.push_back(i == startNodeNumber ? 0 : INF);
		}

		auto comparePriority =
			[this](int node1, int node2)
		{
			return d[node1] > d[node2];
		};

		Q = std::priority_queue<int, std::vector<int>, std::function<bool(int, int)>>(comparePriority);
		Q_copy = std::priority_queue<int, std::vector<int>, std::function<bool(int, int)>>(comparePriority);
		for(size_t i = 0; i < this->graph.getSize(); ++i)
		{
			Q.push(i);
		}

		previous.reserve(this->graph.getSize());
		for(size_t i = 0; i < this->graph.getSize(); ++i)
		{
			previous.push_back(-1);
		}
	}

	void Dijkstra::updateBoard()
	{
		for(auto toUpdate : boardTilesToUpdate)
		{
			for(int i = 0; i < this->inputInfo.board.size(); ++i)
			{
				for(int j = 0; j < this->inputInfo.board[i].size(); ++j)
				{
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
