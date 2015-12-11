#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include "GameEngine.h"
class InputHandler
{

private:
	struct key{
		bool pressed = false;
		SDL_Keycode keycode;
	};

public:
	void Init();
	void CheckInput(GameEngine* game);
	
	key key1;
	key key2;
	key key3;
	key keyCtrl;
	key keyG;
	key keyS;
	key keyA;
	key keyC;
	key keyQ;
	key keyW;
	key keyPLUS;
	key keyMINUS;
	key KeyEscape;
	key keyRunUp;
	key keyRunLeft;
	key keyRunRight;
	key keyRunDown;
};
#endif
