
#ifndef _BALLSELECTOR_H
#define	_BALLSELECTOR_H

#include "Surface.h"
#include "defs.h"
#include "Ball.h"
#include "Texto.h"
#include "Checkbox.h"

class BallSelector {
	
	private:
		SDL_Surface* ballSelectorSurface;
		SDL_Surface* ballBgSurface;
		
		Ball redBall;
		Ball pinkBall;
		Ball blueBall;
		Ball greenBall;

		Texto text;

		int selected;

	public:
		BallSelector();

		int x, y;
		bool visible;
		bool hasCpuCheckbox;

		bool init();
		void render(SDL_Surface*);
		void cleanup();

		void setText(char*);
		void clicked(int mX, int mY);
		int getSelected();

		enum colors {
			NONE = 0,
			RED,
			GREEN,
			BLUE,
			PINK
		};

		Texto isCpuText;
		Checkbox isCpuCheckbox;

		bool isCpu(){
			return isCpuCheckbox.checked;
		}
};

#endif