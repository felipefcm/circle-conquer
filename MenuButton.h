
#ifndef _MENUBUTTON_H
#define _MENUBUTTON_H

#include "Botao.h"

class Menu;

class MenuButton : public Botao<Menu> {
	
	private:

	public:
		MenuButton();

		bool init(Menu* pParent, void (Menu::*pFunction)(void));
};

#endif