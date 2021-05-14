
#ifndef _BALL_H
#define _BALL_H

#include "Surface.h"

class Ball {

	private:
		SDL_Surface* ballSurface;

	public:
		Ball();

		float x, y;

		bool load(char* imageFile);
		void render(SDL_Surface*);
		void cleanup();
};

#endif