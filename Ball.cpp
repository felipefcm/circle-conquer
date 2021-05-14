
#include "Ball.h"

Ball::Ball(){
	ballSurface = NULL;
	
	x = 0;
	y = 0;
}

bool Ball::load(char *imageFile){

	ballSurface = Surface::OnLoad(imageFile);

	if(ballSurface == NULL)
		return false;

	return true;
}

void Ball::render(SDL_Surface *destSurface){
	
	if(!destSurface)
		return;

	Surface::OnDraw(destSurface, ballSurface, (int)x, (int)y); 
}

void Ball::cleanup(){
	
	if(ballSurface)
		SDL_FreeSurface(ballSurface);

	ballSurface = NULL;
}