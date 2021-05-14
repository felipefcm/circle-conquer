
#include "CircleConquer.h"

bool CircleConquer::init(){
	
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
		return false;

	if(TTF_Init() < 0)
		return false;

	displaySurface = SDL_SetVideoMode(WND_WIDTH, WND_HEIGHT, COLOR_DEPTH, SDL_HWSURFACE | SDL_DOUBLEBUF);

	if(displaySurface == NULL)
		return false;

	if(!gameMenu.init())
		return false;

	return true;
}