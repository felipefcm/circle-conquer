
#include "Texto.h"

Texto::Texto(){
	font = NULL;
	fontSurface = NULL;
	texto = NULL;
	x = y = 0;
	visivel = true;

	fgColor.r = 255;
	fgColor.g = 255;
	fgColor.b = 255;

	bgColor.r = 0;
	bgColor.g = 0;
	bgColor.b = 0;

	blended = true;
}

bool Texto::onLoad(char* fontFile, int size){

	font = TTF_OpenFont(fontFile,size);
	return (font != NULL);
}

void Texto::onRender(SDL_Surface* destSurface){
	if(visivel && destSurface != NULL && fontSurface != NULL)
		Surface::OnDraw(destSurface,fontSurface, (int)x, (int)y);
}

void Texto::refreshSurface(){
	if(font)
	{
		if(fontSurface)
		{
			SDL_FreeSurface(fontSurface);
			fontSurface = NULL;
		}

		if(blended)
			fontSurface = TTF_RenderText_Blended(font, texto, fgColor);
		else
			fontSurface = TTF_RenderText_Shaded(font,texto,fgColor,bgColor);	
	}
}

void Texto::setText(char *str){
	texto = str;
	refreshSurface();
}

void Texto::setBlended(bool b){
	blended = b;
}

void Texto::onCleanup(){
	
	if(font)
		TTF_CloseFont(font);

	if(fontSurface)
		SDL_FreeSurface(fontSurface);

	font = NULL;
	fontSurface = NULL;
}

SDL_Surface* Texto::getTextSurface(){
	return fontSurface;
}

void Texto::center(){
	x = (float) WND_WIDTH / 2.0f - fontSurface->w / 2;
	y = (float) WND_HEIGHT / 2.0f;
}

void Texto::centerX(int left, int right){
	if(fontSurface)
		x = (float) (left + right) / 2 - fontSurface->w / 2;
}

void Texto::centerY(int top, int bottom){
	if(fontSurface)
		y = (float) (top + bottom) / 2 - fontSurface->h / 2;
}

int Texto::getWidth(){
	return fontSurface->w;
}

int Texto::getHeight(){
	return fontSurface->h;
}

void Texto::setVisivel(bool v){
	visivel = v;
}

void Texto::setFgColor(Uint8 r, Uint8 g, Uint8 b){
	fgColor.r = r;
	fgColor.g = g;
	fgColor.b = b;
}

void Texto::setBgColor(Uint8 r, Uint8 g, Uint8 b){
	bgColor.r = r;
	bgColor.g = g;
	bgColor.b = b;
}

float Texto::getX(){
	return x;
}

float Texto::getY(){
	return y;	
}

void Texto::setPos(float x, float y){
	
	if(x < 0 || y < 0)
		return;

	this->x = x;
	this->y = y;
}