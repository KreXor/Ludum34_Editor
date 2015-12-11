#ifndef MAPSTATE_H
#define MAPSTATE_H

#include "SDL2/SDL.h"
#include "State.h"
#include "InputHandler.h"
#include "Map.h"
#include "TileMenu.h"

class MapState : public State
{
public:
	void Init(GameEngine* game);
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents(GameEngine* game);
	void Update(GameEngine* game);
	void Draw(GameEngine* game);

	static MapState* Instance() {
		return &m_IntroState;
	}

protected:
	MapState() { }

private:
	static MapState m_IntroState;
	InputHandler inputHandler;
	SDL_Surface* bg;
	SDL_Surface* fader;
	int alpha;
	Map map;
	TileMenu tileMenu;
	int SelectedTile = 0;
	int PreSelectedTile = 0;
	int workinglayer = 0;
	
};

#endif
