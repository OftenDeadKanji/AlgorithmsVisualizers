#include "pch.h"
#include "model.h"
#include "../pathFinding/finder/dijkstra.h"
#include "../pathFinding/finder/A_star.h"

namespace PFAV::MVC
{
	Model::Model()
	{
		std::cout << "Setting board size to 10x10! (in MVC::Model constructor)\n";
		this->setBoardSize(10);
	}
	void Model::update()
	{
		switch(this->state)
		{
		case State::eStartFindingPath:
			if(this->canStartFindingPath())
			{
				if(thread.joinable())
				{
					thread.join();
				}

				this->state = State::eFindingPath;
				this->shouldContinueFindingPath = true;

				thread = std::thread(&Model::findPath, this);
			}
			else
			{
				this->state = State::eIdle;
			}
			break;
		default:
			break;
		}
	}
	void Model::findPath()
	{
		std::unique_ptr<Core::Finder> finder;
		switch(this->chosenAlgorithm)
		{
		case Core::Finder::Algorithm::eDijkstra:
			finder = std::make_unique<Core::Dijkstra>(Core::Dijkstra(Core::InputInfo(startPosX, startPosY, endPosX, endPosY, board, shouldContinueFindingPath)));
			finder->findPath();
			break;
		case Core::Finder::Algorithm::eA_star:
			finder = std::make_unique<Core::A_star>(Core::A_star(Core::InputInfo(startPosX, startPosY, endPosX, endPosY, board, shouldContinueFindingPath)));
			finder->findPath();
			break;
		default:
			break;
		}
	}
	const std::vector<std::vector<Core::Tile>>& Model::getBoard() const
	{
		return this->board;
	}

	void Model::setBoardSize(int size)
	{
		if(size <= 0)
		{
			return;
		}

		this->board.resize(size);
		for(auto& v : this->board)
		{
			v.resize(size);
		}

		if(startPosX >= size || startPosY >= size)
		{
			startPosX = startPosY = -1;
		}

		if(endPosX >= size || endPosY >= size)
		{
			endPosX = endPosY = -1;
		}
	}

	bool Model::canStartFindingPath() const
	{
		return this->startPosX >= 0
			&& this->startPosY >= 0
			&& this->endPosX >= 0
			&& this->endPosY >= 0;
	}

	void Model::changeToPreviousAlgorithm()
	{
		if(chosenAlgorithm != Core::Finder::Algorithm::eFirst)
		{
			this->chosenAlgorithm = static_cast<Core::Finder::Algorithm>(static_cast<int>(this->chosenAlgorithm) - 1);
		}
	}

	void Model::changeToNextAlgorithm()
	{
		if(this->chosenAlgorithm != Core::Finder::Algorithm::eA_star)
		{
			this->chosenAlgorithm = static_cast<Core::Finder::Algorithm>(static_cast<int>(this->chosenAlgorithm) + 1);
		}
	}

	Core::Finder::Algorithm Model::getChosenAlgorithm() const
	{
		return this->chosenAlgorithm;
	}

	void Model::increaseBoardSize()
	{
		this->setBoardSize(this->board.size() + 10);
	}

	void Model::decreaseBoardSize()
	{
		this->setBoardSize(this->board.size() - 10);
	}

	void Model::setTileType(int x, int y, Core::Tile::Type type)
	{
		switch(type)
		{
		case Core::Tile::Type::eStart:
			setNewStartTile(x, y);
			break;
		case Core::Tile::Type::eEnd:
			setNewEndTile(x, y);
			break;
		default:
			setNewOtherTypeTile(x, y, type);
			break;
		}
		this->board[x][y].type = type;
	}

	void Model::startFindingPath()
	{
		this->shouldContinueFindingPath = false;
		this->state = State::eStartFindingPath;
	}

	void Model::stopFindingPath()
	{
		this->shouldContinueFindingPath = false;
		if(this->state == State::eFindingPath)
		{
			this->state = State::eStopped;
		}
	}

	void Model::prepareToExit()
	{
		this->shouldContinueFindingPath = false;

		if(this->thread.joinable())
		{
			this->thread.join();
		}
	}

	void Model::reset()
	{
		this->shouldContinueFindingPath = false;
		if(this->thread.joinable())
		{
			this->thread.join();
		}

		for(auto& column : this->board)
		{
			for(auto& tile : column)
			{
				if(tile.type == Core::Tile::Type::eConsidered || tile.type == Core::Tile::Type::ePath)
				{
					tile.type = Core::Tile::Type::eEmpty;
				}
			}
		}

		this->state = State::eIdle;
	}

	void Model::setNewStartTile(int x, int y)
	{
		if(this->board[x][y].type == Core::Tile::Type::eEnd)
		{
			endPosX = endPosY = -1;
		}

		if(startPosX != -1 && startPosY != -1)
		{
			this->board[startPosX][startPosY].type = Core::Tile::Type::eEmpty;
		}

		startPosX = x;
		startPosY = y;
	}

	void Model::setNewEndTile(int x, int y)
	{
		if(this->board[x][y].type == Core::Tile::Type::eStart)
		{
			startPosX = startPosY = -1;
		}

		if(endPosX != -1 && endPosY != -1)
		{
			this->board[endPosX][endPosY].type = Core::Tile::Type::eEmpty;
		}

		endPosX = x;
		endPosY = y;
	}

	void Model::setNewOtherTypeTile(int x, int y, Core::Tile::Type)
	{
		if(this->board[x][y].type == Core::Tile::Type::eStart)
		{
			startPosX = startPosY = -1;
		}
		else if(this->board[x][y].type == Core::Tile::Type::eEnd)
		{
			endPosX = endPosY = -1;
		}
	}
}
