
#include "CircleConquer.h"

CircleConquer::CircleConquer(){
	
	displaySurface = NULL;

	running = false;

	gameState = MENU;

	version = 0.9f;
}

int CircleConquer::execute(){

	if(!init())
		return -1;

	SDL_Event e;

	running = true;

	while(running){
		
		while(SDL_PollEvent(&e))
			Event::OnEvent(&e);

		loop();

		render();
	}

	cleanup();
	
	return 0;
}

bool CircleConquer::initMatch(){

	if(match.isInit())
		match.cleanup();

	MatchInitData initData;

	gameMenu.getMatchInitData(&initData);

	if(gameState == MENU && gameMenu.menuType == gameMenu.NEWGAME_MENU)
	{			
		if(!match.init(&initData))
		{
			gameMenu.invalidInitMatchMessage(true);
			return false;
		}
		else
		{	
			gameMenu.invalidInitMatchMessage(false);
			gameState = IN_GAME;
		}
	}

	return true;
}


