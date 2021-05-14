
#ifndef		_MATCHSTATS_H
#define		_MATCHSTATS_H

#include "Texto.h"
#include "Botao.h"

struct MatchInitData;

class MatchStats {

	private:
		SDL_Surface* statsSurface;
		int x, y;
		int numPlayers;
		int playerColors[4];

	public:
		MatchStats();

		bool init(MatchInitData*);
		void render(SDL_Surface*);
		void cleanup();

		void setPos(int, int);
		void setX(int);
		void setY(int);
};

#endif
