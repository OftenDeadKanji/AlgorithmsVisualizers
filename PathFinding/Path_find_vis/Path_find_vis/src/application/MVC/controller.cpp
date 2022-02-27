#include "pch.h"
#include "controller.h"

namespace PFAV::MVC
{
	Controller::Controller()
		: view(*this)
	{
		this->view.passBoard(this->model.getBoard());
	}

	void Controller::checkUserInput()
	{
		this->view.checkEvents();
	}

	void Controller::modelUpdate()
	{
		this->model.update();
	}

	void Controller::viewRender()
	{
		this->setViewModelObjects();
		this->view.updateView();
		this->view.render();
	}

	bool Controller::getShouldApplicationClose() const
	{
		return this->shouldApplicationClose;
	}

	void Controller::setShouldApplicationClose(bool newValue)
	{
		this->shouldApplicationClose = newValue;
	}

	void Controller::closeWindowCallback()
	{
		this->model.prepareToExit();
		this->shouldApplicationClose = true;
	}

	void Controller::exitButtonCallback()
	{
		this->model.prepareToExit();
		this->shouldApplicationClose = true;
	}

	void Controller::startButtonCallback()
	{
		if(this->model.canStartFindingPath())
		{
			this->view.disableStartButton();
			this->view.enableResetButton();
				
			this->model.startFindingPath();
		}
	}

	void Controller::resetButtonCallback()
	{
		this->view.disableResetButton();
		this->view.enableStartButton();

		this->model.reset();
	}

	void Controller::setTileTypeCallback(int x, int y, Core::Tile::Type type)
	{
		model.setTileType(x, y, type);
	}

	void Controller::previousAlgorithmButtonCallback()
	{
		this->model.changeToPreviousAlgorithm();
	}

	void Controller::nextAlgorithmButtonCallback()
	{
		this->model.changeToNextAlgorithm();
	}

	void Controller::increaseBoardSizeButtonCallback()
	{
		this->model.increaseBoardSize();
	}

	void Controller::decreaseBoardSizeButtonCallback()
	{
		this->model.decreaseBoardSize();
	}

	void Controller::setViewModelObjects()
	{
		this->view.passModelAlgorithm(this->model.getChosenAlgorithm());
	}

}
