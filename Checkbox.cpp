
#include "Checkbox.h"

Checkbox::Checkbox(){
	
	checkboxSurface = NULL;

	checked = false;

	x = 0;
	y = 0;

	bgColor.r = 0;
	bgColor.g = 0;
	bgColor.b = 0;

	fgColor.r = 255;
	fgColor.g = 255;
	fgColor.b = 255;

	size = 20;
}

void Checkbox::toogle(){
	checked = !checked;
}

bool Checkbox::init(int d){
	
	if(d <= 0)
		return false;
	else
		size = d;

	SDL_Surface* temp = NULL;

	temp = SDL_CreateRGBSurface(0, size, size, COLOR_DEPTH, 0, 0, 0, 0);

	checkboxSurface = SDL_DisplayFormat(temp);

	SDL_FreeSurface(temp);
	temp = NULL;

	if(!checkboxSurface)
		return false;

	return true;
}

void Checkbox::render(SDL_Surface* destSurface){

	SDL_Rect rect;

	rect.x = 3;
	rect.y = 3;
	rect.w = size - 6;
	rect.h = size - 6;

	SDL_FillRect(checkboxSurface, NULL, SDL_MapRGB(checkboxSurface->format, bgColor.r, bgColor.g, bgColor.b));

	if(checked)
		SDL_FillRect(checkboxSurface, &rect, SDL_MapRGB(checkboxSurface->format, fgColor.r, fgColor.g, fgColor.b));

	Surface::OnDraw(destSurface, checkboxSurface, x, y);
}

void Checkbox::cleanup(){
	
	if(checkboxSurface)
		SDL_FreeSurface(checkboxSurface);

	checkboxSurface = NULL;
}

bool Checkbox::clicked(int mX, int mY){
	
	if( mX >= x && mX <= x + size )
		if( mY >= y && mY <= y + size )
			return true;

	return false;
}