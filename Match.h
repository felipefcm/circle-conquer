
#ifndef		_MATCH_H
#define		_MATCH_H

#include <cstdlib>
#include <vector>

#include "Surface.h"
#include "Ball.h"
#include "Board.h"
#include "Texto.h"
#include "FPS.h"
#include "MatchStats.h"

struct MatchInitData {
	int numPlayers;
	bool isCpu[4];
	int playerColors[4];
};

class Match {

	private:
		Board board;
		bool inited;
		int numPlayers;
		bool isCpu[4];
		int cpuThinkTime;

		MatchStats matchStats;

		Texto playerTurnText;
		Texto p1Text;
		Texto p2Text;
		Texto p3Text;
		Texto p4Text;
		Texto escToExitText;

		enum playerColor {
			RED = 1,
			GREEN,
			BLUE,
			PINK
		};

		playerColor playerColors[4];

		bool initTexts();

		void setPlayerColors(MatchInitData*);
		void addInitialCircles();
		void colorText(Texto*, playerColor);

		void nextTurn();
		bool hasPlayChoices(playerColor);
		bool hasEmptyCells();

		void makeCpuMove();

	public:
		Match();

		enum matchStates {
			NONE = 0,
			P1_TURN,
			P2_TURN,
			P3_TURN,
			P4_TURN,
			END_MATCH
		};

		matchStates matchState;

		bool init(MatchInitData*);
		void loop();
		void render(SDL_Surface*);
		void cleanup();

		bool validMatchInitData(MatchInitData*);
		bool isInit();

		void LButtonDown(int mX, int mY);
		void clickedInBoard(int mX, int mY);
};

#endif