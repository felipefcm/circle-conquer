
#include "BallSelector.h"

BallSelector::BallSelector(){
	
	ballSelectorSurface = NULL;
	ballBgSurface = NULL;

	x = 0;
	y = 0;

	visible = false;

	selected = NONE;
	hasCpuCheckbox = true;
}

bool BallSelector::init(){

	SDL_Surface* temp = NULL;

	temp = SDL_CreateRGBSurface(0, 103, 148, COLOR_DEPTH, 0, 0, 0, 0);

	ballSelectorSurface = SDL_DisplayFormat(temp);

	if(!ballSelectorSurface)
		return false;

	SDL_FreeSurface(temp);
	temp = NULL;

	if((ballBgSurface = Surface::OnLoad("images/cell_bg.png")) == NULL)
		return false;

	if(!isCpuText.onLoad("fonts/cro.ttf", 12))
		return false;
	isCpuText.setText("CPU");

	if(!isCpuCheckbox.init(12))
		return false;
	isCpuCheckbox.fgColor.r = 0;
	isCpuCheckbox.fgColor.g = 0;
	isCpuCheckbox.fgColor.b = 0;
	isCpuCheckbox.bgColor.r = 255;
	isCpuCheckbox.bgColor.g = 255;
	isCpuCheckbox.bgColor.b = 255;

	//Selector Draw
	
	SDL_FillRect(ballSelectorSurface, NULL, SDL_MapRGB(ballSelectorSurface->format, 0, 0, 0));

	//Ball squares

	Surface::OnDraw(ballSelectorSurface, ballBgSurface, x + 1, y + 31);
	Surface::OnDraw(ballSelectorSurface, ballBgSurface, x + 1, y + 82);
	Surface::OnDraw(ballSelectorSurface, ballBgSurface, x + 52, y + 82);
	Surface::OnDraw(ballSelectorSurface, ballBgSurface, x + 52, y + 31);

	//balls
	if(!redBall.load("images/redBall.png"))
		return false;
	if(!blueBall.load("images/blueBall.png"))
		return false;
	if(!greenBall.load("images/greenBall.png"))
		return false;
	if(!pinkBall.load("images/pinkBall.png"))
		return false;
	
	redBall.x = (float) x + 1;
	redBall.y = (float) y + 31;

	blueBall.x = (float) x + 52;
	blueBall.y = (float) y + 31;

	greenBall.x = (float) x + 1;
	greenBall.y = (float) y + 82;

	pinkBall.x = (float) x + 52;
	pinkBall.y = (float) y + 82;

	redBall.render(ballSelectorSurface);
	blueBall.render(ballSelectorSurface);
	greenBall.render(ballSelectorSurface);
	pinkBall.render(ballSelectorSurface);

	redBall.cleanup();
	greenBall.cleanup();
	blueBall.cleanup();
	pinkBall.cleanup();

	if(!text.onLoad("fonts/cro.ttf",22))
		return false;
	
	return true;
}

void BallSelector::render(SDL_Surface* destSurface){
	
	if(visible)
	{
		Surface::OnDraw(destSurface, ballSelectorSurface, x, y);
		text.onRender(destSurface);

		if(hasCpuCheckbox)
		{
			isCpuText.onRender(destSurface);
			isCpuCheckbox.render(destSurface);
		}
	}
}

void BallSelector::cleanup(){
	
	if(ballSelectorSurface)
		SDL_FreeSurface(ballSelectorSurface);

	ballSelectorSurface = NULL;

	if(ballBgSurface)
		SDL_FreeSurface(ballBgSurface);

	ballBgSurface = NULL;

	isCpuCheckbox.cleanup();

	text.onCleanup();
	isCpuText.onCleanup();
}

void BallSelector::setText(char* str){
	text.setText(str);

	text.setPos(text.getX(), (float) y + 2);
	text.centerX(x, x + 103);
}

void BallSelector::clicked(int mX, int mY){
	
	if( mX >= x && mX < x + 148 )
		if(mY >= y && mY < y + 148)
		{
			//click in cpuCheckbox
			if(hasCpuCheckbox)
				if(isCpuCheckbox.clicked(mX,mY))
					isCpuCheckbox.toogle();

			//click in red ball
			if(mX >= x + redBall.x && mX < x + redBall.x + 50)
				if(mY >= y + redBall.y && mY < y + redBall.y + 50)
				{
					text.setFgColor(239,15,15);
					text.refreshSurface();
					selected = RED;
				}

			//green
			if(mX >= x + greenBall.x && mX < x + greenBall.x + 50)
				if(mY >= y + greenBall.y && mY < y + greenBall.y + 50)
				{
					text.setFgColor(0,171,12);
					text.refreshSurface();
					selected = GREEN;
				}

			//blue
			if(mX >= x + blueBall.x && mX < x + blueBall.x + 50)
				if(mY >= y + blueBall.y && mY < y + blueBall.y + 50)
				{
					text.setFgColor(1,31,179);
					text.refreshSurface();
					selected = BLUE;
				}

			//pink
			if(mX >= x + pinkBall.x && mX < x + pinkBall.x + 50)
				if(mY >= y + pinkBall.y && mY < y + pinkBall.y + 50)
				{
					text.setFgColor(235,7,232);
					text.refreshSurface();
					selected = PINK;
				}
		}
			

	
}

int BallSelector::getSelected(){
	return selected;
}

