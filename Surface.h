//==============================================================================
// Surface functions
//==============================================================================
#ifndef _Surface_H_
    #define _Surface_H_

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

//==============================================================================
class Surface {
	public:
		Surface();

	public:
		static SDL_Surface* OnLoad(char* File);

		static bool OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y);

		static bool OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y, int X2, int Y2, int W, int H);

		static bool Transparent(SDL_Surface *dest, int R, int G, int B);
};

//==============================================================================

#endif