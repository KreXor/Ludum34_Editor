#include "InputHandler.h"
#include <iostream>

void InputHandler::Init()
{
	keyG.keycode = SDLK_g;
	KeyEscape.keycode = SDLK_ESCAPE;

	keyRunUp.keycode = SDLK_UP;
	keyRunLeft.keycode = SDLK_LEFT;
	keyRunRight.keycode = SDLK_RIGHT;
	keyRunDown.keycode = SDLK_DOWN;

}
void InputHandler::CheckInput(GameEngine* game)
{

	SDL_Event event;



	while (SDL_PollEvent(&event))
	{
		// SDL_QUIT event has come in, quit.
		if (event.type == SDL_QUIT)
		{
			SDL_Quit();
			exit(1);
		}



		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_RIGHT){
				keyRunRight.pressed = true;
			}

			if (event.key.keysym.sym == SDLK_LEFT){
				keyRunLeft.pressed = true;
			}
			if (event.key.keysym.sym == SDLK_UP){
				keyRunUp.pressed = true;

			}
			if (event.key.keysym.sym == SDLK_DOWN){
				keyRunDown.pressed = true;
			}

			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				SDL_Quit();
				exit(1);
			}
			if (event.key.keysym.sym == SDLK_KP_PLUS)
			{
				keyPLUS.pressed = true;
				//game->camera.zoomIn();
			}
			if (event.key.keysym.sym == SDLK_KP_MINUS)
			{
				keyMINUS.pressed = true;
				//game->camera.zoomOut();
			}

			if (event.key.keysym.sym == SDLK_g)
			{
				keyG.pressed = true;
			}

			if (event.key.keysym.sym == SDLK_s)
			{
				keyS.pressed = true;
			}
			if (event.key.keysym.sym == SDLK_c)
			{
				keyC.pressed = true;
			}


			if (event.key.keysym.sym == SDLK_1){
				key1.pressed = true;
			}

			if (event.key.keysym.sym == SDLK_2){
				key2.pressed = true;
			}
			if (event.key.keysym.sym == SDLK_3){
				key3.pressed = true;

			}
			if (event.key.keysym.sym == SDLK_LCTRL){
				keyCtrl.pressed = true;

			}
			if (event.key.keysym.sym == SDLK_a){
				keyA.pressed = true;

			}

			if (event.key.keysym.sym == SDLK_q){
				keyQ.pressed = true;

			}

			if (event.key.keysym.sym == SDLK_w){
				keyW.pressed = true;

			}
			
		}

		if (event.type == SDL_KEYUP)
		{
			if (event.key.keysym.sym == SDLK_RIGHT){
				keyRunRight.pressed = false;
			}

			if (event.key.keysym.sym == SDLK_LEFT){
				keyRunLeft.pressed = false;
			}
			if (event.key.keysym.sym == SDLK_UP){
				keyRunUp.pressed = false;

			}
			if (event.key.keysym.sym == SDLK_DOWN){
				keyRunDown.pressed = false;
			}

			if (event.key.keysym.sym == SDLK_g){
				keyG.pressed = false;
			}

			if (event.key.keysym.sym == SDLK_s)
			{
				keyS.pressed = false;
			}
			if (event.key.keysym.sym == SDLK_1){
				key1.pressed = false;
			}

			if (event.key.keysym.sym == SDLK_2){
				key2.pressed = false;
			}
			if (event.key.keysym.sym == SDLK_3){
				key3.pressed = false;

			}
			if (event.key.keysym.sym == SDLK_a){
				keyA.pressed = false;

			}
			if (event.key.keysym.sym == SDLK_LCTRL){
				keyCtrl.pressed = false;

			}
			if (event.key.keysym.sym == SDLK_KP_PLUS)
			{
				keyPLUS.pressed = false;
			}
			if (event.key.keysym.sym == SDLK_KP_MINUS)
			{
				keyMINUS.pressed = false;
			}
			if (event.key.keysym.sym == SDLK_c)
			{
				keyC.pressed = false;
			}

			if (event.key.keysym.sym == SDLK_q){
				keyQ.pressed = false;

			}

			if (event.key.keysym.sym == SDLK_w){
				keyW.pressed = false;

			}
		}

	}
}

	
