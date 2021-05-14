
#ifndef _CHECKBOX_H
#define	_CHECKBOX_H

#include "Surface.h"
#include "defs.h"

class Checkbox {
	
	private:
		SDL_Surface* checkboxSurface;
		int size;

	public:
		Checkbox();

		bool checked;
		int x, y;
		SDL_Color bgColor, fgColor;

		bool init(int d = 20);
		void render(SDL_Surface*);
		void cleanup();

		void toogle();
		bool clicked(int mX, int mY);
};

#endif