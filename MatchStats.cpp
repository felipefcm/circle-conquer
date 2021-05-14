
#include "MatchStats.h"

MatchStats::MatchStats(){

	statsSurface = NULL;

	x = y = 0;
}

bool MatchStats::init(MatchInitData* pData){

	SDL_Surface* temp = NULL;

	if((temp = SDL_CreateRGBSurface(0, 500, 300, COLOR_DEPTH, 0, 0, 0, 0)) == NULL)
		return false;

	if((statsSurface = SDL_DisplayFormat(temp)) == NULL)
		return false;

	SDL_FreeSurface(temp);

	SDL_FillRect(statsSurface, NULL, SDL_MapRGB(statsSurface->format, 30, 30, 30));

	return true;
}

void MatchStats::render(SDL_Surface* destSurface){
	Surface::OnDraw(destSurface, statsSurface, x, y);
}

void MatchStats::cleanup(){
	
}

