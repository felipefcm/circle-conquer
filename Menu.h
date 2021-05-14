
#ifndef _MAINMENU_H
#define	_MAINMENU_H

#include "defs.h"
#include "Surface.h"
#include "Checkbox.h"
#include "Texto.h"
#include "BallSelector.h"
#include "Botao.h"
#include "MenuButton.h"
#include "Match.h"

class Menu {
	
	private:
		SDL_Surface* mainMenuSurface;
		SDL_Surface* newGameMenuSurface;
		SDL_Surface* creditsSurface;

		// ----------------- MAIN_MENU
		Texto gameTitleText;
		MenuButton newGameButton;
		MenuButton creditsButton;
		MenuButton exitButton;
		Texto returnToGameText;
		// ---------------------------

		// ----------------- NEWGAME_MENU
		Texto newGameMenuText;
		Texto numPlayersText;
		Texto playersText;
		Texto colorText;
		Texto invalidOptionsText;
		Botao<Menu> cancelNewGameButton;
		Botao<Menu> playButton;
		// ------------------------------

		// ----------------- CREDITS
		Botao<Menu> creditsBackButton;
		Texto		creditsText;
		// -------------------------

		void checkClickInCheckboxes(int mX, int mY);
		void checkClickInSelectors(int mX, int mY);
		void checkClickInButtons(int mX, int mY);

		bool initButtons();

		bool drawMenuBox(SDL_Surface*&);
		bool drawMainMenu();
		bool drawNewGameMenu();
		bool drawCredits();

	public:
		Menu();

		enum menuTypes {
			MAIN_MENU = 1,
			NEWGAME_MENU,
			CREDITS
		};

		//Qual menu será exibido
		menuTypes menuType;

		//O usuario fechou o jogo pelo menu?
		bool exitedFromMenu;

		bool playPressed;

		bool existMatch;

		// ----------------- NEWGAME_MENU
		Checkbox twoPlayersCheckbox;
		Checkbox threePlayersCheckbox;
		Checkbox fourPlayersCheckbox;

		BallSelector pSelector;
		BallSelector sSelector;
		BallSelector tSelector;
		BallSelector qSelector;
		//-------------------------------

		//Button actions
		//MAIN_MENU
		void newGamePressed();
		void creditsPressed();
		void exitPressed();
		
		//NEWGAME_MENU
		void playButtonPressed();

		void backMainMenu();

		void getMatchInitData(MatchInitData*);
		void invalidInitMatchMessage(bool visible);

		bool init();
		void render(SDL_Surface*);
		void cleanup();

		void LMouseDown(int mX, int mY);
};

#endif