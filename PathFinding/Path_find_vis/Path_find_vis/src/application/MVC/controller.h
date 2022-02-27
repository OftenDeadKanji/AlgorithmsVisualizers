#pragma once
#include "model.h"
#include "view.h"

namespace PFAV
{
	namespace MVC
	{
		class Controller
		{
		public:
			Controller();

			void checkUserInput();
			void modelUpdate();
			void viewRender();

			bool getShouldApplicationClose() const;
			void setShouldApplicationClose(bool);

		#pragma region Events callbacks
			void closeWindowCallback();
			void exitButtonCallback();
			void startButtonCallback();
			void resetButtonCallback();
			void setTileTypeCallback(int x, int y, Core::Tile::Type);
			void previousAlgorithmButtonCallback();
			void nextAlgorithmButtonCallback();
			void increaseBoardSizeButtonCallback();
			void decreaseBoardSizeButtonCallback();
		#pragma endregion

		private:
			void setViewModelObjects();

			Model model;
			View view;

			bool shouldApplicationClose = false;
		};
	}
}