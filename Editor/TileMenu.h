#ifndef TILEMENU_H
#define TILEMENU_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "GameEngine.h"
#include <string.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include "rapidjson/document.h"
#include <math.h>
#include <vector>
#include "Map.h"
#include "SDL2/SDL_ttf.h"

class TileMenu
{

private:
	typedef struct
	{
		SDL_Texture* text;
		SDL_Rect rect;
	} textObject;

	vector<textObject> textBuffer;

public:
	int tileSize = 1;
	int tilesPerRow = 32;
	int nrRows = 4;
	int viewPage = 0;
	void Init(GameEngine* game);
	void Draw(GameEngine* game, Map map, int selectedTile, int layer);
	TileMenu();
	textObject AddTextString(std::string text, SDL_Renderer* renderer, SDL_Color text_color, int posX, int posY, int fontSize);
	void ChangeZoomText(GameEngine* game, std::string text);
	void ChangeTilePageText(GameEngine* game, std::string text);
	
};


#endif
