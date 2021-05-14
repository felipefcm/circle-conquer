
#include "Menu.h"

bool Menu::init(){

	//Desenha objetos estáticos
	if(!drawMainMenu() || !drawNewGameMenu() || !drawCredits())
		return false;

	if(!initButtons())
		return false;
	
	return true;
}

bool Menu::initButtons(){
	
	SDL_Rect rect;
	rect.x = rect.y = 0;

// ------------------------------------------------- MAIN_MENU
	if(!newGameButton.init(this, &Menu::newGamePressed))
		return false;
	newGameButton.setText("New Game");
	newGameButton.centerX(MENU_X, MENU_X + 600);
	newGameButton.setY(150);

	if(!creditsButton.init(this, &Menu::creditsPressed))
		return false;
	creditsButton.setText("Credits");
	creditsButton.centerX(MENU_X, MENU_X + 600);
	creditsButton.setY(220);

	if(!exitButton.init(this, &Menu::exitPressed))
		return false;
	exitButton.setText("Exit");
	exitButton.centerX(MENU_X, MENU_X + 600);
	exitButton.setY(350);
// -----------------------------------------------------------

// ------------------------------------------------- NEW GAME
	rect.w = 115;
	rect.h = 30;
	if(!cancelNewGameButton.init(this, &Menu::backMainMenu,"fonts/cro.ttf", 24, NULL))
		return false;
	cancelNewGameButton.setText("Cancel");
	cancelNewGameButton.setRect(&rect);
	cancelNewGameButton.setX(125);
	cancelNewGameButton.setY(435);

	if(!playButton.init(this, &Menu::playButtonPressed,"fonts/cro.ttf", 24, NULL))
		return false;
	playButton.setText("Play!");
	playButton.setRect(&rect);
	playButton.setX(560);
	playButton.setY(435);
// ----------------------------------------------------------
	
// ------------------------------------------------- CREDITS
	rect.w = 100;
	rect.h = 25;
	if(!creditsBackButton.init(this, &Menu::backMainMenu,"fonts/cro.ttf", 24, NULL))
		return false;
	creditsBackButton.setText("Back");
	creditsBackButton.setRect(&rect);
	creditsBackButton.centerX(MENU_X, MENU_X + 600);
	creditsBackButton.setY(MENU_Y + 360);
// ---------------------------------------------------------
	
	return true;
}
