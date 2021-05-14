
#include "Menu.h"

Menu::Menu(){
	mainMenuSurface = NULL;
	newGameMenuSurface = NULL;
	creditsSurface = NULL;

	exitedFromMenu = false;
	playPressed = false;
	existMatch = false;

	menuType = MAIN_MENU;
	//menuType = NEWGAME_MENU;
}

void Menu::render(SDL_Surface* destSurface){
	
	if(!destSurface)
		return;

	switch(menuType)
	{
		case MAIN_MENU:

				Surface::OnDraw(destSurface, mainMenuSurface, MENU_X, MENU_Y);

				gameTitleText.onRender(destSurface);
				newGameButton.render(destSurface);
				creditsButton.render(destSurface);
				exitButton.render(destSurface);

				if(existMatch)
					returnToGameText.onRender(destSurface);
		break;

		case NEWGAME_MENU:
				
				Surface::OnDraw(destSurface, newGameMenuSurface, MENU_X, MENU_Y);

				newGameMenuText.onRender(destSurface);
				playersText.onRender(destSurface);
				numPlayersText.onRender(destSurface);
				invalidOptionsText.onRender(destSurface);

				twoPlayersCheckbox.render(destSurface);
				threePlayersCheckbox.render(destSurface);
				fourPlayersCheckbox.render(destSurface);

				colorText.onRender(destSurface);

				pSelector.render(destSurface);
				sSelector.render(destSurface);
				tSelector.render(destSurface);
				qSelector.render(destSurface);

				cancelNewGameButton.render(destSurface);
				playButton.render(destSurface);
		break;

		case CREDITS:
				Surface::OnDraw(destSurface, creditsSurface, MENU_X, MENU_Y);

				creditsText.onRender(destSurface);

				creditsBackButton.render(destSurface);
		break;
	}
}

void Menu::cleanup(){
	
	if(mainMenuSurface)
		SDL_FreeSurface(mainMenuSurface);

	mainMenuSurface = NULL;

	if(newGameMenuSurface)
		SDL_FreeSurface(newGameMenuSurface);

	newGameMenuSurface = NULL;

	if(creditsSurface)
		SDL_FreeSurface(creditsSurface);

	creditsSurface = NULL;

	gameTitleText.onCleanup();

	newGameMenuText.onCleanup();
	playersText.onCleanup();
	numPlayersText.onCleanup();
	creditsText.onCleanup();
	invalidOptionsText.onCleanup();
	returnToGameText.onCleanup();

	twoPlayersCheckbox.cleanup();
	threePlayersCheckbox.cleanup();
	fourPlayersCheckbox.cleanup();

	colorText.onCleanup();

	pSelector.cleanup();
	sSelector.cleanup();
	tSelector.cleanup();
	qSelector.cleanup();

	newGameButton.cleanup();
	cancelNewGameButton.cleanup();
	creditsButton.cleanup();
	exitButton.cleanup();
	creditsBackButton.cleanup();
	playButton.cleanup();
}

void Menu::checkClickInCheckboxes(int mX, int mY){
	
	if(menuType != NEWGAME_MENU)
		return;

	if(twoPlayersCheckbox.clicked(mX,mY))
	{
		twoPlayersCheckbox.toogle();

		if(twoPlayersCheckbox.checked)
		{
			threePlayersCheckbox.checked = false;
			fourPlayersCheckbox.checked = false;

			pSelector.visible = true;
			sSelector.visible = true;
			tSelector.visible = false;
			qSelector.visible = false;

			sSelector.setText("P2");
		}
	}

	if(threePlayersCheckbox.clicked(mX,mY))
	{
		threePlayersCheckbox.toogle();

		if(threePlayersCheckbox.checked)
		{
			twoPlayersCheckbox.checked = false;
			fourPlayersCheckbox.checked = false;

			pSelector.visible = true;
			sSelector.visible = true;
			tSelector.visible = true;
			qSelector.visible = false;

			sSelector.setText("P2");
		}
	}

	if(fourPlayersCheckbox.clicked(mX,mY))
	{
		fourPlayersCheckbox.toogle();

		if(fourPlayersCheckbox.checked)
		{
			twoPlayersCheckbox.checked = false;
			threePlayersCheckbox.checked = false;

			pSelector.visible = true;
			sSelector.visible = true;
			tSelector.visible = true;
			qSelector.visible = true;

			sSelector.setText("P2");
		}
	}
}

void Menu::checkClickInSelectors(int mX, int mY){
	
	if(menuType != NEWGAME_MENU)
		return;

	pSelector.clicked(mX,mY);
	sSelector.clicked(mX,mY);
	tSelector.clicked(mX,mY);
	qSelector.clicked(mX,mY);
}

void Menu::LMouseDown(int mX, int mY){
	
	checkClickInCheckboxes(mX,mY);
	checkClickInSelectors(mX,mY);
	checkClickInButtons(mX,mY);
}

void Menu::checkClickInButtons(int mX, int mY){
	
	switch(menuType)
	{
		case MAIN_MENU:
			newGameButton.checkClick(mX,mY);
			creditsButton.checkClick(mX,mY);
			exitButton.checkClick(mX,mY);
		break;

		case NEWGAME_MENU:
			cancelNewGameButton.checkClick(mX,mY);
			playButton.checkClick(mX,mY);
		break;

		case CREDITS:
			creditsBackButton.checkClick(mX,mY);
		break;	
	}
}

void Menu::getMatchInitData(MatchInitData* pData){

	//Pega todas as cores, as que tiverem índice maior que (numPlayers - 1) serão ignorados
	pData->playerColors[0] = pSelector.getSelected();
	pData->playerColors[1] = sSelector.getSelected();
	pData->playerColors[2] = tSelector.getSelected();
	pData->playerColors[3] = qSelector.getSelected();

	pData->isCpu[0] = pSelector.isCpu();
	pData->isCpu[1] = sSelector.isCpu();
	pData->isCpu[2] = tSelector.isCpu();
	pData->isCpu[3] = qSelector.isCpu();

	//Dois players sempre devem existir
	pData->numPlayers = 2;

	if(threePlayersCheckbox.checked)
		pData->numPlayers = 3;
	else if(fourPlayersCheckbox.checked)
		pData->numPlayers = 4;

	bool disp[4];
	for(int i=0; i< 4; i++)
		disp[i] = true;

	for(int i=0; i< pData->numPlayers; i++)
		disp[pData->playerColors[i]] = (pData->playerColors[i] == Match::NONE);

	//if player has no color, assign one avaliable
	for(int i=0; i< pData->numPlayers; i++)
		for(int j=0; pData->playerColors[i] == Match::NONE; j++)
			if(disp[j])
			{
				pData->playerColors[i] = j+1;
				disp[j] = false;
			}
		
}

void Menu::invalidInitMatchMessage(bool visible){
	invalidOptionsText.setVisivel(visible);
}

