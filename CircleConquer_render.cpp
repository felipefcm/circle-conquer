
#include "CircleConquer.h"

void CircleConquer::render(){

	SDL_FillRect(displaySurface, NULL, SDL_MapRGB(displaySurface->format, 0, 0, 0));

	if(gameState == MENU)
		gameMenu.render(displaySurface);
	else if(gameState == IN_GAME)
			match.render(displaySurface);

	SDL_Flip(displaySurface);
}