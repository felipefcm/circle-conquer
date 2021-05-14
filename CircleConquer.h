
#ifndef _CIRCLECONQ_H
#define _CIRCLECONQ_H

#include <SDL\SDL.h>

#include "Event.h"
#include "Surface.h"
#include "FPS.h"
#include "defs.h"
#include "Ball.h"
#include "Menu.h"
#include "Match.h"

class CircleConquer : Event {

	private:

		float version;

		enum gameStates {
			MENU = 1,
			IN_GAME,
			END_GAME
		};

		bool running;
		SDL_Surface* displaySurface;
		char windowTitle[50];
		int gameState;
		Menu gameMenu;
		Match match;

		int mX, mY;

	public:
		CircleConquer();

		bool init();
		int execute();
		void loop();
		void render();
		void cleanup();

		bool initMatch();

		//Event
		void OnExit();
		void OnLButtonDown(int mX, int mY);
		void OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle);
		void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
		void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);
};

#endif

