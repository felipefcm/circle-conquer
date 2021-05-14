
#include "Board.h"

Board::Board(){

	boardSurface = NULL;
	cellBgSurface = NULL;
	x = y = 0;

	for(int i=0; i < 9; i++)
		for(int j=0; j < 12; j++)
			grid[i][j] = NOT_INIT;
}

void Board::render(SDL_Surface* destSurface){
	if(destSurface && boardSurface)
		Surface::OnDraw(destSurface, boardSurface, x, y);
}

void Board::cleanup(){
	
	if(boardSurface)
		SDL_FreeSurface(boardSurface);

	boardSurface = NULL;

	if(cellBgSurface)
		SDL_FreeSurface(cellBgSurface);
	
	cellBgSurface = NULL;

	redBall.cleanup();
	greenBall.cleanup();
	blueBall.cleanup();
	pinkBall.cleanup();

	x = y = 0;
}

//Desenha a surface inteira
void Board::refreshSurface(){
	
	for(int i = 0; i < 9; i++)
		for(int j = 0; j < 12; j++)
		{
			switch(grid[i][j])
			{
				case NOT_INIT:
					break;

				case EMPTY:
					Surface::OnDraw(boardSurface, cellBgSurface, j * 50, i * 50); 
					break;

				case BALL_RED:
					redBall.x = (float) j * 50;
					redBall.y = (float) i * 50;
					Surface::OnDraw(boardSurface, cellBgSurface, j * 50, i * 50); 
					redBall.render(boardSurface);
					break;

				case BALL_GREEN:
					greenBall.x = (float) j * 50;
					greenBall.y = (float) i * 50;
					Surface::OnDraw(boardSurface, cellBgSurface, j * 50, i * 50); 
					greenBall.render(boardSurface);
					break;

				case BALL_BLUE:
					blueBall.x = (float) j * 50;
					blueBall.y = (float) i * 50;
					Surface::OnDraw(boardSurface, cellBgSurface, j * 50, i * 50); 
					blueBall.render(boardSurface);
					break;

				case BALL_PINK:
					pinkBall.x = (float) j * 50;
					pinkBall.y = (float) i * 50;
					Surface::OnDraw(boardSurface, cellBgSurface, j * 50, i * 50); 
					pinkBall.render(boardSurface);
					break;

				case BLOCK:
					break;
			}
		}
}

bool Board::loadMap(int m){

	char fileName[40];

	sprintf_s(fileName,"maps/%d.map", m);

	return loadMap(fileName);
}

bool Board::loadMap(char *mapFile){
	
	std::ifstream file;
	int ballColor;

	file.open(mapFile);

	if(!file.good() || file.fail())
		return false;

	for(int l=0; l<9; l++)
		for(int c=0; c<12; c++)
		{
			if(file.eof())
				return false;

			file >> std::skipws >> ballColor;
			grid[l][c] = (gridConstants) ballColor;
		}

	file.close();

	refreshSurface();

	return true;
}

void Board::centerX(int left, int right){
	x = (left + right) / 2 - 50 * 12 / 2;
}

void Board::centerY(int top, int bottom){
	y = (top + bottom) / 2 - 50 * 9 / 2;
}

void Board::setPos(int linha, int coluna, gridConstants v){
	
	if(linha < 0 || linha >= 9)
		if(coluna < 0 || coluna >= 12)
			return;

	grid[linha][coluna] = v;
	refreshCell(linha,coluna);
}

void Board::refreshCell(int linha, int coluna){

	switch(grid[linha][coluna])
	{
		case NOT_INIT:
			break;

		case EMPTY:
			Surface::OnDraw(boardSurface, cellBgSurface, coluna * 50, linha * 50); 
			break;

		case BALL_RED:
			redBall.x = (float) coluna * 50;
			redBall.y = (float) linha * 50;
			Surface::OnDraw(boardSurface, cellBgSurface, coluna * 50, linha * 50); 
			redBall.render(boardSurface);
			break;

		case BALL_GREEN:
			greenBall.x = (float) coluna * 50;
			greenBall.y = (float) linha * 50;
			Surface::OnDraw(boardSurface, cellBgSurface, coluna * 50, linha * 50); 
			greenBall.render(boardSurface);
			break;

		case BALL_BLUE:
			blueBall.x = (float) coluna * 50;
			blueBall.y = (float) linha * 50;
			Surface::OnDraw(boardSurface, cellBgSurface, coluna * 50, linha * 50); 
			blueBall.render(boardSurface);
			break;

		case BALL_PINK:
			pinkBall.x = (float) coluna * 50;
			pinkBall.y = (float) linha * 50;
			Surface::OnDraw(boardSurface, cellBgSurface, coluna * 50, linha * 50); 
			pinkBall.render(boardSurface);
			break;

		case BLOCK:
			//TODO: Draw block
			break;
	}
}

int Board::getX(){
	return x;
}

int Board::getY(){
	return y;
}

void Board::getBoardPosFromPoint(int mX, int mY, BoardPos* pos){

	if(pos == NULL)
		return;

	pos->coluna = (mX - x) / 50;
	pos->linha = (mY - y) / 50;
}

Board::gridConstants Board::getPos(int linha, int coluna){
	
	if(linha < 0 || linha > 8)
		return NOT_INIT;
	
	if(coluna < 0 || coluna > 11)
		return NOT_INIT;

	return grid[linha][coluna];
}

void Board::changeNearCirclesToColor(int linha, int coluna, gridConstants c){
	
	//Acima
	if( getPos(linha-1, coluna) > 0 && getPos(linha-1, coluna) != c )
		setPos(linha-1, coluna, c);

	//Direita
	if( getPos(linha, coluna+1) > 0 && getPos(linha, coluna+1) != c )
		setPos(linha, coluna+1, c);

	//Baixo
	if( getPos(linha+1, coluna) > 0 && getPos(linha+1, coluna) != c )
		setPos(linha+1, coluna, c);

	//Esquerda
	if( getPos(linha, coluna-1) > 0 && getPos(linha, coluna-1) != c )
		setPos(linha, coluna-1, c);
}

bool Board::canBeTakenByColor(int linha, int coluna, gridConstants c){

	if(getPos(linha,coluna) != EMPTY)
		return false;

	//Acima
	if( getPos(linha-1, coluna) == c || 
	   (getPos(linha-1, coluna) > 0 && getPos(linha-2, coluna) == c ) )
		return true;

	//Direita
	if( getPos(linha, coluna+1) == c || 
	   (getPos(linha, coluna+1) > 0 && getPos(linha, coluna+2) == c ) )
		return true;

	//Baixo
	if( getPos(linha+1, coluna) == c || 
	   (getPos(linha+1, coluna) > 0 && getPos(linha+2, coluna) == c ) )
		return true;

	//Esquerda
	if( getPos(linha, coluna-1) == c || 
	   (getPos(linha, coluna-1) > 0 && getPos(linha, coluna-2) == c ) )
		return true;

	return false;
}