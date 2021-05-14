
#include "Board.h"

bool Board::init(){
	
	SDL_Surface* temp = NULL;

	temp = SDL_CreateRGBSurface(SDL_HWSURFACE, 600, 450, COLOR_DEPTH, 0, 0, 0, 0);

	if(temp == NULL)
		return false;

	boardSurface = SDL_DisplayFormat(temp);

	SDL_FreeSurface(temp);
	temp = NULL;

	if((cellBgSurface = Surface::OnLoad("images/cell_bg.png")) == NULL)
		return false;

	//Balls
	if(!redBall.load("images/redBall.png"))
		return false;
	if(!greenBall.load("images/greenBall.png"))
		return false;
	if(!blueBall.load("images/blueBall.png"))
		return false;
	if(!pinkBall.load("images/pinkBall.png"))
		return false;

	loadMap(1);

	return true;
}