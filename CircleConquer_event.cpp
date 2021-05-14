
#include "CircleConquer.h"

void CircleConquer::OnExit(){
	running = false;
}

void CircleConquer::OnLButtonDown(int mX, int mY){
	
	if(gameState == MENU)
		gameMenu.LMouseDown(mX, mY);

	if(gameState == IN_GAME)
		match.LButtonDown(mX,mY);
}

void CircleConquer::OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle){
	this->mX = mX;
	this->mY = mY;
}

void CircleConquer::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode){

}

void CircleConquer::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode){

	switch(sym)
	{
		case SDLK_RETURN:

			initMatch();

		break;

		case SDLK_ESCAPE:
			switch(gameState)
			{
				case IN_GAME:
					gameState = MENU;
					gameMenu.menuType = Menu::MAIN_MENU;
					gameMenu.existMatch = true;
				break;

				case MENU:
					if(match.isInit())
						gameState = IN_GAME;
				break;
			}
		break;
	}
}