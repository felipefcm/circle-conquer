
#include "Match.h"

bool Match::init(MatchInitData* pData){

	if(!validMatchInitData(pData))
		return false;

	numPlayers = pData->numPlayers;

	isCpu[0] = pData->isCpu[0];
	isCpu[1] = pData->isCpu[1];
	isCpu[2] = pData->isCpu[2];
	isCpu[3] = pData->isCpu[3];

	setPlayerColors(pData);

	if(!board.init())
		return false;
	board.centerX(0, WND_WIDTH);
	board.centerY(0, WND_HEIGHT);

	if(!initTexts())
		return false;

	addInitialCircles();

	if(!matchStats.init(pData))
		return false;

	srand( SDL_GetTicks() );

	nextTurn();

	inited = true;
	return true;
}

bool Match::initTexts(){

	if(!playerTurnText.onLoad("fonts/cro.ttf", 24))
		return false;
	playerTurnText.setText("Somebody's turn!");
	playerTurnText.centerX(0, WND_WIDTH);
	playerTurnText.setPos(playerTurnText.getX(), 40);

	if(!p1Text.onLoad("fonts/cro.ttf", 18))
		return false;
	p1Text.setText("Player 1");
	p1Text.setPos(50,48);
	colorText(&p1Text, playerColors[0]);
	p1Text.refreshSurface();

	if(!p2Text.onLoad("fonts/cro.ttf", 18))
		return false;
	p2Text.setText("Player 2");
	p2Text.setPos(650,530);
	colorText(&p2Text, playerColors[1]);
	p2Text.refreshSurface();

	if(!p3Text.onLoad("fonts/cro.ttf", 18))
		return false;
	p3Text.setText("Player 3");
	p3Text.setPos(50,530);
	colorText(&p3Text, playerColors[2]);
	p3Text.refreshSurface();

	if(numPlayers < 3)
		p3Text.setVisivel(false);

	if(!p4Text.onLoad("fonts/cro.ttf", 18))
		return false;
	p4Text.setText("Player 4");
	p4Text.setPos(650,48);
	colorText(&p4Text, playerColors[3]);
	p4Text.refreshSurface();
	
	if(numPlayers < 4)
		p4Text.setVisivel(false);

	if(!escToExitText.onLoad("fonts/cro.ttf", 18))
		return false;
	escToExitText.setText("Press ESC to leave match");
	escToExitText.centerX(0, WND_WIDTH);
	escToExitText.setPos(escToExitText.getX(), WND_HEIGHT - 30);
	
	return true;
}

void Match::addInitialCircles(){
	
	//Sempre há dois jogadores ou mais
	board.setPos(0, 0, (Board::gridConstants) playerColors[0]);
	board.setPos(8, 11, (Board::gridConstants) playerColors[1]);

	switch(numPlayers)
	{
		case 3:
			board.setPos(8, 0, (Board::gridConstants) playerColors[2]);
		break;

		case 4:
			board.setPos(8, 0, (Board::gridConstants) playerColors[2]);
			board.setPos(0, 11, (Board::gridConstants) playerColors[3]);
		break;
	}
}

void Match::setPlayerColors(MatchInitData* pData){
	playerColors[0] = (playerColor) pData->playerColors[0];
	playerColors[1] = (playerColor) pData->playerColors[1];
	playerColors[2] = (playerColor) pData->playerColors[2];
	playerColors[3] = (playerColor) pData->playerColors[3];
}
