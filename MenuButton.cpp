
#include "MenuButton.h"

MenuButton::MenuButton(){

}

bool MenuButton::init(Menu* pParent, void (Menu::*pFunction)(void)){
	
	if(!Botao::init(pParent, pFunction, "fonts/cro.ttf", 24, NULL))
		return false;

	SDL_Rect rect;

	rect.x = rect.y = 0;
	rect.w = 250;
	rect.h = 60;

	Botao::setRect(&rect);

	return true;
}
