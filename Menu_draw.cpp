
#include "Menu.h"

bool Menu::drawMenuBox(SDL_Surface*& destSurface){

	if(destSurface != NULL)
		return false;
	
	SDL_Surface* tempSurface = NULL;

	tempSurface = SDL_CreateRGBSurface(0, 600, 400, COLOR_DEPTH, 0, 0, 0, 0);

	if(tempSurface == NULL)
		return false;

	destSurface = SDL_DisplayFormat(tempSurface);

	if(destSurface == NULL)
		return false;

	SDL_FreeSurface(tempSurface);
	tempSurface = NULL;

	SDL_Rect borderRect;

	borderRect.x = MENU_BORDER;
	borderRect.y = MENU_BORDER;
	borderRect.w = 600 - 2 * MENU_BORDER;
	borderRect.h = 400 - 2 * MENU_BORDER;

	//Menu draw
	SDL_FillRect(destSurface, NULL, SDL_MapRGB(destSurface->format, 190, 190, 190));
	SDL_FillRect(destSurface, &borderRect, SDL_MapRGB(destSurface->format, 20, 20, 20));

	return true;
}

bool Menu::drawMainMenu(){

	if(!drawMenuBox(mainMenuSurface))
		return false;

	if(!gameTitleText.onLoad("fonts/cro.ttf",32))
		return false;
	gameTitleText.setText("Circle Conquer");
	gameTitleText.center();
	gameTitleText.setPos(gameTitleText.getX(), MENU_Y + 16);

	if(!returnToGameText.onLoad("fonts/cro.ttf",20))
		return false;
	returnToGameText.setText("Press ESC to resume match");
	returnToGameText.center();
	returnToGameText.setPos(returnToGameText.getX(), WND_HEIGHT - 115);

	if(mainMenuSurface)
		return true;

	return false;
}

bool Menu::drawNewGameMenu(){
	
	if(!drawMenuBox(newGameMenuSurface))
		return false;

	//Textos
	if(!newGameMenuText.onLoad("fonts/cro.ttf", 32))
		return false;
	newGameMenuText.setText("New Game");
	newGameMenuText.centerX(0, WND_WIDTH);
	newGameMenuText.setPos(newGameMenuText.getX(), MENU_Y + 10);

	if(!numPlayersText.onLoad("fonts/cro.ttf", 24))
		return false;
	numPlayersText.setText("Number of players");
	numPlayersText.center();
	numPlayersText.setPos(numPlayersText.getX(), MENU_Y + 58);

	if(!playersText.onLoad("fonts/cro.ttf", 24))
		return false;
	playersText.setText("2          3          4");
	playersText.center();
	playersText.setPos(playersText.getX(), MENU_Y + 85);

	//Player checkboxes
	if( !twoPlayersCheckbox.init() ||
	!threePlayersCheckbox.init() ||
	!fourPlayersCheckbox.init() )
			return false;

	twoPlayersCheckbox.x = MENU_X + 162;
	threePlayersCheckbox.x = MENU_X + 290;
	fourPlayersCheckbox.x = MENU_X + 415;

	twoPlayersCheckbox.y = MENU_Y + 118;
	threePlayersCheckbox.y = MENU_Y + 118;
	fourPlayersCheckbox.y = MENU_Y + 118;

	//Default option
	twoPlayersCheckbox.checked = true;

	if(!colorText.onLoad("fonts/cro.ttf", 24))
		return false;
	colorText.setText("Colors");
	colorText.center();
	colorText.setPos(colorText.getX(), MENU_Y + 145);

		//Selector's
	if( !pSelector.init() ||
		!sSelector.init() ||
		!tSelector.init() ||
		!qSelector.init())
			return false;

	pSelector.x = MENU_X + 40;
	pSelector.y = MENU_Y + 180;
	pSelector.visible = true;
	
	sSelector.x = MENU_X + 178;
	sSelector.y = MENU_Y + 180;
	sSelector.visible = true;
	
	tSelector.x = MENU_X + 316;
	tSelector.y = MENU_Y + 180;
	//tSelector.visible = true;
	
	qSelector.x = MENU_X + 454;
	qSelector.y = MENU_Y + 180;
	//qSelector.visible = true;

	pSelector.setText("P1");
	sSelector.setText("P2");
	tSelector.setText("P3");
	qSelector.setText("P4");

	//Cpu Checkboxes
	pSelector.isCpuCheckbox.x = pSelector.x + 35;
	pSelector.isCpuCheckbox.y = pSelector.y + 134;
	pSelector.isCpuText.setPos((float)pSelector.x + 50, (float)pSelector.y + 132);
	
	//P2 habilitado por default como CPU
	sSelector.isCpuCheckbox.checked = true;
	
	sSelector.isCpuCheckbox.x = sSelector.x + 35;
	sSelector.isCpuCheckbox.y = sSelector.y + 134;
	sSelector.isCpuText.setPos((float)sSelector.x + 50, (float)sSelector.y + 132);

	tSelector.isCpuCheckbox.x = tSelector.x + 35;
	tSelector.isCpuCheckbox.y = tSelector.y + 134;
	tSelector.isCpuText.setPos((float)tSelector.x + 50, (float)tSelector.y + 132);

	qSelector.isCpuCheckbox.x = qSelector.x + 35;
	qSelector.isCpuCheckbox.y = qSelector.y + 134;
	qSelector.isCpuText.setPos((float)qSelector.x + 50, (float)qSelector.y + 132);

	if(!invalidOptionsText.onLoad("fonts/cro.ttf", 22))
		return false;
	invalidOptionsText.setVisivel(false);
	invalidOptionsText.setText("You can't select same colors!");
	invalidOptionsText.centerX(MENU_X, MENU_X + 600);
	invalidOptionsText.setPos(invalidOptionsText.getX(), MENU_Y + 328);

	if(!newGameMenuSurface)
		return false;

	return true;
}

bool Menu::drawCredits(){

	if(!drawMenuBox(creditsSurface))
		return false;

	if(!creditsText.onLoad("fonts/cro.ttf", 32))
		return false;
	creditsText.setText("Credits");
	creditsText.centerX(MENU_X, MENU_X + 600);
	creditsText.setPos(creditsText.getX(), MENU_Y + 20);

	if(!creditsSurface)
		return false;

	return true;
}