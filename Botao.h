
#ifndef _CBOTAO_H
#define _CBOTAO_H

#include "Texto.h"

template <class T>
class Botao : public Texto {

	protected:
		bool visible;

		SDL_Surface* bgSurface;
		SDL_Rect	 buttonBox;
		SDL_Color	 bgColor;

		T*	parent;
		void (T::*action)(void);

	public:
		Botao();

		bool init(T *parent, void (T::*pFunction)(void), char* fontFile, int fontSize, char* bgImageFile, int posX = 0, int posY = 0);
		
		void render(SDL_Surface*);
		void cleanup();

		void setVisible(bool);

		void setX(int);
		void setY(int);
		void setHeight(int);
		void setWidth(int);
		void setRect(SDL_Rect*);

		int getWidth();
		int getHeight();

		void center();
		void centerX(int left, int right);
		void centerY(int top, int bottom);
		void getBoxRect(SDL_Rect*);
		void setButtonBgColor(Uint8 r, Uint8 g, Uint8 b);

		void checkClick(int mX, int mY);
};


#include "Botao.h"

template <class T>
Botao<T>::Botao(){
	
	action = NULL;
	parent = NULL;

	visible = true;
	bgSurface = NULL;
	
	bgColor.r = 0;
	bgColor.g = 0;
	bgColor.b = 0;

	//Default button size
	buttonBox.x = buttonBox.y = 0;
	buttonBox.w = 60;
	buttonBox.h = 30;
}

template <class T>
bool Botao<T>::init(T *pParent, void (T::*pFunction)(void), char* fontFile, int fontSize, char* bgImageFile, int posX, int posY){
	
	//Ponteiro para o membro da classe T que instancia/herda Botao
	if(pParent != NULL && pFunction != NULL)
	{
		action = pFunction;
		parent = pParent;
	}

	if(!Texto::onLoad(fontFile,fontSize))
		return false;

	buttonBox.x = posX;
	buttonBox.y = posY;

	if(bgImageFile != NULL)
	{
		if((bgSurface = Surface::OnLoad(bgImageFile)) == NULL)
			return false;
	}

	return true;
}

template <class T>
void Botao<T>::render(SDL_Surface* destSurface){
	
	if(bgSurface)
		Surface::OnDraw(destSurface, bgSurface, buttonBox.x, buttonBox.y);
	else
		SDL_FillRect(destSurface, &buttonBox, SDL_MapRGB(destSurface->format, bgColor.r, bgColor.g, bgColor.b));
		
	Texto::onRender(destSurface);
}

template <class T>
void Botao<T>::cleanup(){
	
	if(bgSurface)
		SDL_FreeSurface(bgSurface);

	Texto::onCleanup();
}

template <class T>
int Botao<T>::getWidth(){
	return buttonBox.w;
}

template <class T>
int Botao<T>::getHeight(){
	return buttonBox.h;
}

template <class T>
void Botao<T>::center(){
	buttonBox.x = WND_WIDTH / 2 - buttonBox.w / 2;
	buttonBox.y = WND_HEIGHT / 2 - buttonBox.h / 2;
	Texto::centerX(buttonBox.x, buttonBox.x + buttonBox.w);
	Texto::centerY(buttonBox.y, buttonBox.y + buttonBox.h);
}

template <class T>
void Botao<T>::centerX(int left, int right){
	buttonBox.x = (left + right) / 2 - buttonBox.w / 2;
	Texto::centerX(left, right);
}

template <class T>
void Botao<T>::centerY(int top, int bottom){
	buttonBox.y = (top + bottom) / 2 - buttonBox.h / 2;
	Texto::centerY(top, bottom);
}

template <class T>
void Botao<T>::checkClick(int mX, int mY){
	if(mX >= buttonBox.x && mX <= buttonBox.x + buttonBox.w)
		if(mY >= buttonBox.y && mY <= buttonBox.y + buttonBox.h)
			if(action != NULL && parent != NULL)
				(parent->*action)();
}

template <class T>
void Botao<T>::getBoxRect(SDL_Rect *rect){
	rect->x = buttonBox.x;
	rect->y = buttonBox.y;
	rect->w = buttonBox.w;
	rect->h = buttonBox.h;
}

template <class T>
void Botao<T>::setButtonBgColor(Uint8 r, Uint8 g, Uint8 b){
	bgColor.r = r;
	bgColor.g = g;
	bgColor.b = b;
}

template <class T>
void Botao<T>::setX(int x){
	buttonBox.x = x;
	Texto::centerY(buttonBox.y, buttonBox.y + buttonBox.h);
	Texto::centerX(buttonBox.x, buttonBox.x + buttonBox.w);
}

template <class T>
void Botao<T>::setY(int y){
	buttonBox.y = y;
	Texto::centerY(buttonBox.y, buttonBox.y + buttonBox.h);
	Texto::centerX(buttonBox.x, buttonBox.x + buttonBox.w);
}

template <class T>
void Botao<T>::setHeight(int h){
	buttonBox.h = h;
	Texto::centerY(buttonBox.y, buttonBox.y + buttonBox.h);
}

template <class T>
void Botao<T>::setWidth(int w){
	buttonBox.w = w;
	Texto::centerX(buttonBox.x, buttonBox.x + buttonBox.w);
}

template <class T>
void Botao<T>::setRect(SDL_Rect* rect){
	
	if(rect == NULL || rect->w <= 0 || rect->h <= 0)
		return;

	buttonBox = *rect;

	Texto::centerY(buttonBox.y, buttonBox.y + buttonBox.h);
	Texto::centerX(buttonBox.x, buttonBox.x + buttonBox.w);
}

#endif