
#include "Menu.h"

void Menu::newGamePressed(){
	menuType = NEWGAME_MENU;
}

void Menu::backMainMenu(){
	menuType = MAIN_MENU;
}

void Menu::creditsPressed(){
	menuType = CREDITS;
}

void Menu::exitPressed(){
	exitedFromMenu = true;
}

void Menu::playButtonPressed(){
	playPressed = true;
}