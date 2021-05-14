
#ifndef		_BOARD_H
#define		_BOARD_H

#include <fstream>

#include "Surface.h"
#include "Ball.h"
#include "defs.h"

struct BoardPos {
	int linha;
	int coluna;
};

class Board {

	public:
		enum gridConstants {
			NOT_INIT = -1,
			EMPTY,
			BALL_RED,
			BALL_GREEN,
			BALL_BLUE,
			BALL_PINK,
			BLOCK
		};

	private:
		SDL_Surface* boardSurface;

		gridConstants grid[9][12];

		int x, y;
		Ball redBall;
		Ball blueBall;
		Ball greenBall;
		Ball pinkBall;
		SDL_Surface* cellBgSurface;

		bool loadMap(char *mapFile);

		void refreshSurface();
		void refreshCell(int linha, int coluna);

	public:
		Board();

		bool init();
		void render(SDL_Surface*);
		void cleanup();

		bool loadMap(int m);
		void setPos(int linha, int coluna, gridConstants v);
		gridConstants getPos(int linha, int coluna);

		void centerX(int left, int right);
		void centerY(int top, int bottom);

		int getX();
		int getY();

		void getBoardPosFromPoint(int mX, int mY, BoardPos*);
		void changeNearCirclesToColor(int linha, int coluna, gridConstants);
		bool canBeTakenByColor(int linha, int coluna, gridConstants);
};

#endif