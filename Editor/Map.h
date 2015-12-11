#ifndef MAP_H
#define MAP_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "GameEngine.h"
#include <string.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include "rapidjson/document.h"
#include "rapidjson/filewritestream.h"
#include "rapidjson/writer.h"
#include <math.h>
#include <vector>
#include <cstdio>

class Map
{

private:
	struct Position{
		float x;
		float y;
	};

	struct Tile{
		SDL_Rect worldPosition;
		SDL_Rect imagePosition;
		int layer;
		int layer2;
		int type;
		int blockid;
		int boundingBoxType; // so we know if there is gound have a slope or note, see physics.c for more info.
	};

	
	SDL_Texture *Load_image(string filename, GameEngine* game);
	int tile_size;
	int tiles_width_count;
	int tiles_heigth_count;
	int displayLayer = -1;

	void calculateLightPoints();
	void addLightPoint(int x, int y);
	void addLightPointToCorner(Tile tile, int corner);
	void readMapData(GameEngine* game);

	bool showGrid = false;

public:
	SDL_Texture* tilesImage[10];
	vector<SDL_Rect> tileList;
	void ChangeTile(GameEngine* game, int mousePosX, int mousePosY, int tile, int layer);
	void toggleGrid();
	Tile** mapTilePosition;
	void LoadMap(GameEngine* game);
	void Draw(GameEngine* game);
	int getTileSize();
	int getTilesHeightCount();
	int getTilesWidthCount();
	bool isWall(Tile tile);
	vector<Position> lightPoints;

	void save();
	void ChangeTileType(int tile);
	void RemoveLayer(GameEngine* game, int x, int y, int layer);

	void ShowLayer(int layer);

};


#endif
