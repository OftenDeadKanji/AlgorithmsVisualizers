#include "pch.h"
#include "graph.h"

namespace PFAV::Core
{
	void Graph::initializeGraph(const std::vector<std::vector<Tile>>& board, bool withDiagonalNeighbours)
	{
		this->size = board.size() * board.front().size();

		this->initNodes(board);
		this->initWeights(board, withDiagonalNeighbours);
	}

	Weight& Graph::operator()(const GraphNode& from, const GraphNode& to)
	{
		auto fromPosIter = this->nodes.find(from);
		auto toPosIter = this->nodes.find(to);

		if(fromPosIter != this->nodes.end() && toPosIter != this->nodes.end())
		{
			return this->weights[from.number][to.number];
		}

		throw GraphNodeNotFound("This Graph doesn't contain at least one of the given nodes.");
	}

	Weight& Graph::operator()(unsigned int from, unsigned int to)
	{
		if(from < this->size && to < this->size)
		{
			return this->weights[from][to];
		}

		throw GraphNodeNotFound("This Graph doesn't contain at least one of the given nodes.");
	}

	size_t Graph::getSize() const
	{
		return this->size;
	}

	std::vector<const GraphNode*> Graph::getNodeNeighbours(const GraphNode& node)
	{
		std::vector<const GraphNode*> neighbours;
		for(auto iter = this->nodes.begin(); iter != this->nodes.end(); ++iter)
		{
			if(*iter == node)
			{
				continue;
			}

			//if (weight != INF), but it's double so...
			if(std::abs(this->weights[node.number][iter->number] - INF) > std::numeric_limits<double>::epsilon())
			{
				neighbours.push_back(&*iter);
			}
		}

		return neighbours;
	}

	std::vector<const GraphNode*> Graph::getNodeNeighbours(unsigned int nodeNumber)
	{
		std::vector<const GraphNode*> neighbours;
		for(auto iter = this->nodes.begin(); iter != this->nodes.end(); ++iter)
		{
			if(iter->number == nodeNumber)
			{
				continue;
			}

			//if (weight != INF), but it's double so...
			if(std::abs(this->weights[nodeNumber][iter->number] - INF) > std::numeric_limits<double>::epsilon())
			{
				neighbours.push_back(&*iter);
			}
		}

		return neighbours;
	}

	void Graph::clear()
	{
		this->nodes.clear();
		this->weights.clear();

		this->size = -1;
	}

	void Graph::initNodes(const std::vector<std::vector<Tile>>& board)
	{
		unsigned int nodeNumber = 0;
		for(size_t i = 0; i < board.size(); ++i)
		{
			for(size_t j = 0; j < board.front().size(); ++j)
			{
				this->nodes.insert(GraphNode(nodeNumber++, i, j));
			}
		}
	}

	void Graph::initWeights(const std::vector<std::vector<Tile>>& board, bool withDiagonalNeighbours)
	{
		this->weights.resize(this->size);
		for(const auto& currentNode : this->nodes)
		{
			this->weights[currentNode.number].resize(this->size);

			for(const auto& node : this->nodes)
			{
				if(currentNode == node)
				{
					this->weights[currentNode.number][node.number] = 0;
					continue;
				}

				const int xPosDiff = std::abs(static_cast<int>(currentNode.boardPosX - node.boardPosX));
				const int yPosDiff = std::abs(static_cast<int>(currentNode.boardPosY - node.boardPosY));
				Weight weight = INF;

				if(board[node.boardPosX][node.boardPosY].type != Tile::Type::eObstacle)
				{
					if(xPosDiff == 1)
					{
						if(yPosDiff == 0)
						{
							weight = defaultNeighbourWeight;
						}
						else if(withDiagonalNeighbours && yPosDiff == 1)
						{
							weight = diagonalNeighbourWeight;
						}
					}
					else if(xPosDiff == 0 && yPosDiff == 1)
					{
						weight = defaultNeighbourWeight;
					}
				}

				this->weights[currentNode.number][node.number] = weight;
			}
		}
	}
}
