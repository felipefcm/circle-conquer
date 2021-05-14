
#include "CircleConquer.h"

void CircleConquer::cleanup(){

	gameMenu.cleanup();
	match.cleanup();

	if(displaySurface)
		SDL_FreeSurface(displaySurface);

	displaySurface = NULL;

	TTF_Quit();
	SDL_Quit();
}