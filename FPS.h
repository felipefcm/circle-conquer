
#ifndef _FPS_H
#define _FPS_H

#include <SDL\SDL.h>

class FPS {

	private:
		int oldTime;
		int lastTime;
		float speedFactor;
		int numFrames;
		int frames;

	public:
		static FPS fpsControl;

		FPS();
		void OnLoop();
		int getFPS();
		float getSpeedFactor();
};

#endif