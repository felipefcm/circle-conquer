
#include "CircleConquer.h"

void CircleConquer::loop(){

	FPS::fpsControl.OnLoop();

	if(gameMenu.exitedFromMenu)
		OnExit();

	if(gameMenu.playPressed)
	{
		gameMenu.playPressed = false;
		initMatch();
	}

	if(gameState == IN_GAME)
		match.loop();

#ifdef _DEBUG
	sprintf_s(windowTitle, "CircleConquer v%.1f - FPS: %d | (%d,%d)", version, FPS::fpsControl.getFPS(), mX, mY);
	SDL_WM_SetCaption(windowTitle, NULL);
#else
	sprintf_s(windowTitle, "CircleConquer v%.1f", version);
	SDL_WM_SetCaption(windowTitle, NULL);
#endif

	SDL_Delay(3);
}



