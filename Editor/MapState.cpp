#include <stdio.h>

#include "SDL2/SDL.h"
#include "GameEngine.h"
#include "MapState.h"
#include <string>



MapState MapState::m_IntroState;

void MapState::Init(GameEngine* game)
{
	tileMenu.Init(game);
	map.LoadMap(game);
	game->camera.reset();
	game->camera.setPosition(-100, -100);

	string zoomText = std::to_string(game->camera.getZoomLevel());
	this->tileMenu.ChangeZoomText(game, "Zoom Level: " + zoomText.substr(0,4));
}

void MapState::Cleanup()
{


}

void MapState::Pause()
{
}

void MapState::Resume()
{
}

void MapState::HandleEvents(GameEngine* game)
{

}

void MapState::Update(GameEngine* game)
{
	inputHandler.CheckInput(game);
	//game->camera.update(game->millisecondFTime);

	if (inputHandler.keyG.pressed == true){
		map.toggleGrid();
		SDL_Delay(400);
	}

	if (inputHandler.keyS.pressed == true){
		map.save();
		SDL_Delay(1000);
	}
	
	if (inputHandler.keyRunRight.pressed == true){
		game->camera.setPosition(game->camera.getXPosition() - 10, game->camera.getYPosition());
	}

	else if (inputHandler.keyRunLeft.pressed == true){
		game->camera.setPosition(game->camera.getXPosition() + 10, game->camera.getYPosition());
	}
	else if (inputHandler.keyRunUp.pressed == true){
		game->camera.setPosition(game->camera.getXPosition(), game->camera.getYPosition() + 10);
	}
	else if (inputHandler.keyRunDown.pressed == true){
		game->camera.setPosition(game->camera.getXPosition(), game->camera.getYPosition() - 10);
	}
	if (inputHandler.keyC.pressed == true)
	{
		game->camera.setPosition(0, 0);
	}
	if (inputHandler.key1.pressed == true)
	{
		this->workinglayer = 0;
	}
	if (inputHandler.key2.pressed == true)
	{
		this->workinglayer = 1;
	}
	if (inputHandler.key3.pressed == true)
	{
		this->workinglayer = 2;
	}
	if (inputHandler.key4.pressed == true)
	{
		this->workinglayer = 3;
	}
	if (inputHandler.key5.pressed == true)
	{
		this->workinglayer = 4;
	}
	if (inputHandler.keyA.pressed == true && inputHandler.keyCtrl.pressed == true)
	{
		map.ShowLayer(-1);
	}
	if (inputHandler.key1.pressed == true && inputHandler.keyCtrl.pressed == true)
	{
		map.ShowLayer(0);
	}
	if (inputHandler.key2.pressed == true && inputHandler.keyCtrl.pressed == true)
	{
		map.ShowLayer(1);
	}
	if (inputHandler.key3.pressed == true && inputHandler.keyCtrl.pressed == true)
	{
		map.ShowLayer(2);
	}
	if (inputHandler.key4.pressed == true && inputHandler.keyCtrl.pressed == true)
	{
		map.ShowLayer(3);
	}
	if (inputHandler.key5.pressed == true && inputHandler.keyCtrl.pressed == true)
	{
		map.ShowLayer(4);
	}


	if (inputHandler.keyQ.pressed == true)
	{
		if (tileMenu.viewPage > 0)
			tileMenu.viewPage--;

		string pageText = std::to_string(tileMenu.viewPage+1);
		this->tileMenu.ChangeTilePageText(game, "Tile Page: " + pageText);

		SDL_Delay(200);
	}
	if (inputHandler.keyW.pressed == true)
	{
		tileMenu.viewPage++;
		string pageText = std::to_string(tileMenu.viewPage + 1);
		this->tileMenu.ChangeTilePageText(game, "Tile Page: " + pageText);
		SDL_Delay(200);
	}

	int x, y;
	SDL_GetMouseState(&x, &y);

	if (inputHandler.keyPLUS.pressed == true)
	{
		string zoomText = std::to_string(game->camera.getZoomLevel());
		this->tileMenu.ChangeZoomText(game, "Zoom Level: " + zoomText.substr(0, 4));
		int cx = game->camera.getXPosition() - 80;
		int cy = game->camera.getYPosition() - 80;
		game->camera.setPosition(cx, cy);
		game->camera.zoomIn();
	}
	if (inputHandler.keyMINUS.pressed == true)
	{
		string zoomText = std::to_string(game->camera.getZoomLevel());
		this->tileMenu.ChangeZoomText(game, "Zoom Level: " + zoomText.substr(0, 4));
		int cx = game->camera.getXPosition() + 80;
		int cy = game->camera.getYPosition() + 80;
		game->camera.setPosition(cx, cy);
		game->camera.zoomOut();
	}
	
	int tilesPerRow = tileMenu.tilesPerRow;
	int tileIndex = (tileMenu.tilesPerRow * tileMenu.nrRows)*tileMenu.viewPage;
	if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		if (y < game->screenHeigth - 200)
		{
			map.ChangeTile(game, x, y, this->SelectedTile, workinglayer);
		}
		else
		{
			int xtile = floor(x / (map.getTileSize()*tileMenu.tileSize));
			int ytile = floor((y - (game->screenHeigth - 200)) / (map.getTileSize()*tileMenu.tileSize));

	
			if ((xtile + tilesPerRow * ytile) + tileIndex < map.tileList.size())
			{
				this->SelectedTile = (xtile + tilesPerRow*ytile) + tileIndex;
			}
			
		}
	}

	if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT))
	{
		if (y < game->screenHeigth - 200)
		{
			map.RemoveLayer(game, x, y, workinglayer);
		}
		if (y > game->screenHeigth - 200)
		{
			int xtile = floor(x / (map.getTileSize()*tileMenu.tileSize));
			int ytile = floor((y - (game->screenHeigth - 200)) / (map.getTileSize()*tileMenu.tileSize));


			if ((xtile + tilesPerRow * ytile) + tileIndex < map.tileList.size())
			{
				int tmp_tile = (xtile + tilesPerRow * ytile) + tileIndex;
				map.ChangeTileType(tmp_tile);
				SDL_Delay(200);
			}

		}
	}

	if (y > game->screenHeigth - 200)
	{
		int xtile = floor(x / (map.getTileSize()*tileMenu.tileSize));
		int ytile = floor((y - (game->screenHeigth - 200)) / (map.getTileSize()*tileMenu.tileSize));


		if ((xtile + tilesPerRow * ytile) + tileIndex < map.tileList.size())
		{
			this->PreSelectedTile = (xtile + tilesPerRow * ytile) + tileIndex;
		}

	}
}

void MapState::Draw(GameEngine* game)
{
	map.Draw(game);

	int x, y;
	SDL_GetMouseState(&x, &y);
	if (y > game->screenHeigth - 200)
	{
		tileMenu.Draw(game, map, this->PreSelectedTile, workinglayer);
	}
	else
	{
		tileMenu.Draw(game, map, this->SelectedTile, workinglayer);
	}
	

}
