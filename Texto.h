
#ifndef _TEXTO_H
#define _TEXTO_H

#include <SDL\SDL_ttf.h>

#include "Surface.h"
#include "defs.h"

class Texto {

	protected:
		SDL_Surface* fontSurface;
		bool blended;
		float x;
		float y;

	private:
		char *texto;
		bool visivel;
		TTF_Font* font;
		SDL_Color	fgColor;
		SDL_Color	bgColor;

	public:
		Texto();
		
		void refreshSurface();

		void setText(char *str);
		void setVisivel(bool);
		void setBlended(bool);
		void setFgColor(Uint8 r, Uint8 g, Uint8 b);
		void setBgColor(Uint8 r, Uint8 g, Uint8 b);
		void center();
		void centerX(int left,int right);
		void centerY(int top, int bottom);
		int getWidth();
		int getHeight();
		bool onLoad(char* fontFile, int size);
		SDL_Surface* getTextSurface();
		virtual void onRender(SDL_Surface* destSurface);
		void onCleanup();
		float getX();
		float getY();
		void setPos(float x,float y);
};

#endif