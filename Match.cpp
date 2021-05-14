
#include "Match.h"

Match::Match(){
	inited = false;
	
	matchState = NONE;
	numPlayers = 0;
	cpuThinkTime = 0;

	isCpu[0] = false;
	isCpu[1] = false;
	isCpu[2] = false;
	isCpu[3] = false;
}

void Match::loop(){
	
	//Se é vez do computador, jogue!
	if(matchState != END_MATCH)
		if( isCpu[matchState-1] )
		{

#ifdef _DEBUG
			if(cpuThinkTime >= FPS::fpsControl.getFPS() * 0)
#else
			if(cpuThinkTime >= FPS::fpsControl.getFPS() * 0.7)
#endif
			{
				makeCpuMove();
				cpuThinkTime = 0;
			}
			else
				cpuThinkTime++;
		}
}

void Match::render(SDL_Surface* destSurface){
	
	board.render(destSurface);

	playerTurnText.onRender(destSurface);
	p1Text.onRender(destSurface);
	p2Text.onRender(destSurface);
	p3Text.onRender(destSurface);
	p4Text.onRender(destSurface);
	escToExitText.onRender(destSurface);

	//Match Stats
	if(matchState == END_MATCH)
		matchStats.render(destSurface);
}

void Match::cleanup(){
	
	board.cleanup();

	playerTurnText.onCleanup();
	p1Text.onCleanup();
	p2Text.onCleanup();
	p3Text.onCleanup();
	p4Text.onCleanup();
	escToExitText.onCleanup();

	matchStats.cleanup();

	inited = false;
}

bool Match::validMatchInitData(MatchInitData* pData){

	switch(pData->numPlayers)
	{
		case 2:
			if(pData->playerColors[0] == 0 || pData->playerColors[1] == 0 )
					return false;

			if(pData->playerColors[0] == pData->playerColors[1])
				return false;
		break;

		case 3:
			if(pData->playerColors[0] == 0 || pData->playerColors[1] == 0 ||
			   pData->playerColors[2] == 0 )
					return false;

			if( pData->playerColors[0] == pData->playerColors[1] ||
				pData->playerColors[0] == pData->playerColors[2] ||
				pData->playerColors[1] == pData->playerColors[2] )
					return false;
		break;

		case 4:
			if(pData->playerColors[0] == 0 || pData->playerColors[1] == 0 ||
			   pData->playerColors[2] == 0 || pData->playerColors[3] == 0 )
					return false;

			if( pData->playerColors[0] == pData->playerColors[1] ||
				pData->playerColors[0] == pData->playerColors[2] ||
				pData->playerColors[0] == pData->playerColors[3] ||
				pData->playerColors[1] == pData->playerColors[2] ||
				pData->playerColors[1] == pData->playerColors[3] ||
				pData->playerColors[2] == pData->playerColors[3] )
					return false;
		break;
	}

	return true;
}

bool Match::isInit(){
	return inited;
}

void Match::LButtonDown(int mX, int mY){
	
	//Click in Board?
	if(mX >= board.getX() && mX <= board.getX() + 12 * 50)
		if(mY >= board.getY() && mY <= board.getY() + 9 * 50)
			clickedInBoard(mX, mY);
}

void Match::clickedInBoard(int mX, int mY){
	
	BoardPos pos;

	board.getBoardPosFromPoint(mX, mY, &pos);

	//Só são tratados cliques em espaços livres
	if( board.getPos( pos.linha, pos.coluna ) != Board::EMPTY )
		return;

	switch(matchState)
	{
		case P1_TURN:
			if(isCpu[matchState-1])
				return;

			if( board.canBeTakenByColor( pos.linha, pos.coluna, (Board::gridConstants) playerColors[0] ) )
			{
				board.setPos(pos.linha, pos.coluna, (Board::gridConstants) playerColors[0]);
				board.changeNearCirclesToColor(pos.linha, pos.coluna, (Board::gridConstants) playerColors[0]);
				nextTurn();
			}
		break;

		case P2_TURN:
			if(isCpu[matchState-1])
				return;

			if( board.canBeTakenByColor( pos.linha, pos.coluna, (Board::gridConstants) playerColors[1] ) )
			{
				board.setPos(pos.linha, pos.coluna, (Board::gridConstants) playerColors[1]);
				board.changeNearCirclesToColor(pos.linha, pos.coluna, (Board::gridConstants) playerColors[1]);
				nextTurn();
			}
		break;

		case P3_TURN:
			if(isCpu[matchState-1])
				return;

			if( board.canBeTakenByColor( pos.linha, pos.coluna, (Board::gridConstants) playerColors[2] ) )
			{
				board.setPos(pos.linha, pos.coluna, (Board::gridConstants) playerColors[2]);
				board.changeNearCirclesToColor(pos.linha, pos.coluna, (Board::gridConstants) playerColors[2]);
				nextTurn();
			}
		break;

		case P4_TURN:
			if(isCpu[matchState-1])
				return;

			if( board.canBeTakenByColor( pos.linha, pos.coluna, (Board::gridConstants) playerColors[3] ) )
			{
				board.setPos(pos.linha, pos.coluna, (Board::gridConstants) playerColors[3]);
				board.changeNearCirclesToColor(pos.linha, pos.coluna, (Board::gridConstants) playerColors[3]);
				nextTurn();
			}
		break;
	}
}

void Match::colorText(Texto* pText, playerColor pCol){
	
	if(pText == NULL)
		return;

	switch(pCol)
	{
		case RED:
			pText->setFgColor(239,15,15);
		break;

		case GREEN:
			pText->setFgColor(0,171,12);
		break;

		case BLUE:
			pText->setFgColor(1,31,179);
		break;

		case PINK:
			pText->setFgColor(235,7,232);
		break;
	}
}

void Match::nextTurn(){

	if(!hasEmptyCells())
	{
		matchState = END_MATCH;
		playerTurnText.setFgColor(255,255,255);
		playerTurnText.setText("Match Over!");
		playerTurnText.centerX(0, WND_WIDTH);
		return;
	}

	//Próximo turno
	if(matchState == NONE)
	{
		//Sorteia primeiro jogador a jogar
		matchState = (matchStates) (rand() % numPlayers + 1);
	}
	else
	{
		if( matchState < numPlayers )
			matchState = (matchStates) ((int) matchState + 1);
		else
			matchState = P1_TURN;
	}

	if(!hasPlayChoices(playerColors[matchState-1]))
		nextTurn();
	
	switch(matchState)
	{
		case P1_TURN:
			colorText(&playerTurnText, playerColors[0]);
			if(isCpu[matchState-1])
				playerTurnText.setText("Player 1 turn! (CPU)");
			else
				playerTurnText.setText("Player 1 turn!");
			playerTurnText.centerX(0, WND_WIDTH);
		break;

		case P2_TURN:
			colorText(&playerTurnText, playerColors[1]);
			if(isCpu[matchState-1])
				playerTurnText.setText("Player 2 turn! (CPU)");
			else
				playerTurnText.setText("Player 2 turn!");
			playerTurnText.centerX(0, WND_WIDTH);
		break;

		case P3_TURN:
			colorText(&playerTurnText, playerColors[2]);
			if(isCpu[matchState-1])
				playerTurnText.setText("Player 3 turn! (CPU)");
			else
				playerTurnText.setText("Player 3 turn!");
			playerTurnText.centerX(0, WND_WIDTH);
		break;

		case P4_TURN:
			colorText(&playerTurnText, playerColors[3]);
			if(isCpu[matchState-1])
				playerTurnText.setText("Player 4 turn! (CPU)");
			else
				playerTurnText.setText("Player 4 turn!");
			playerTurnText.centerX(0, WND_WIDTH);
		break;
	}
}

void Match::makeCpuMove(){

	struct situation {
		BoardPos pos;
		int quality;
	};

	std::vector<situation> candidatesList;
	
	for(int linha=0; linha<9; linha++)
		for(int coluna=0; coluna<12; coluna++)
			if( board.canBeTakenByColor( linha, coluna, (Board::gridConstants) playerColors[matchState-1] ) )
			{
				situation aSituation;
				aSituation.quality = 0;

				//Acima
				if( board.getPos(linha-1, coluna) > 0 && board.getPos(linha-1, coluna) != playerColors[matchState-1] )
					aSituation.quality++;

				//Direita
				if( board.getPos(linha, coluna+1) > 0 && board.getPos(linha, coluna+1) != playerColors[matchState-1] )
					aSituation.quality++;

				//Baixo
				if( board.getPos(linha+1, coluna) > 0 && board.getPos(linha+1, coluna) != playerColors[matchState-1] )
					aSituation.quality++;

				//Esquerda
				if( board.getPos(linha, coluna-1) > 0 && board.getPos(linha, coluna-1) != playerColors[matchState-1] )
					aSituation.quality++;
				
				BoardPos pos;
				pos.linha = linha;
				pos.coluna = coluna;

				aSituation.pos = pos;

				candidatesList.push_back(aSituation);
			}

	//Escolhe melhor situação, se houver mais de uma, sorteia
	int max = 0;

	std::vector<BoardPos> bestPosList;

	for(unsigned int i=0; i<candidatesList.size(); i++)
		if(candidatesList[i].quality >= max)
			max = candidatesList[i].quality;

	for(unsigned int i=0; i<candidatesList.size(); i++)
		if(candidatesList[i].quality == max)
			bestPosList.push_back(candidatesList[i].pos);

	BoardPos pos;

	//Pelo menos uma solução existe
	if(bestPosList.size() == 1)
	{
		pos = bestPosList[0];
	}
	else
	{
		int sol = rand() % bestPosList.size();
		pos = bestPosList[sol];
	}

	board.setPos(pos.linha, pos.coluna, (Board::gridConstants) playerColors[matchState-1]);
	board.changeNearCirclesToColor(pos.linha, pos.coluna, (Board::gridConstants) playerColors[matchState-1]);

	candidatesList.clear();
	bestPosList.clear();

	nextTurn();
}

bool Match::hasPlayChoices(playerColor c){

	for(int i=0; i< 9; i++)
		for(int j=0; j<12; j++)
			if(board.getPos(i,j) == Board::EMPTY)	
				if( board.canBeTakenByColor(i, j, (Board::gridConstants) c) )
					return true;
	
	return false;
}

bool Match::hasEmptyCells(){

	unsigned int vazias = 0;

	for(int i=0; i< 9; i++)
		for(int j=0; j<12; j++)
			if(board.getPos(i,j) == Board::EMPTY)
				vazias++;

	return (vazias != 0);
}


