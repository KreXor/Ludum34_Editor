#include "TileMenu.h"
#include <string>
TileMenu::TileMenu()
{
	

}

void TileMenu::Init(GameEngine* game)
{
	textBuffer.push_back(AddTextString("Type: Wall", game->renderer, { 0, 0, 0 }, game->screenWidth - 320, game->screenHeigth - 190, 16));
	textBuffer.push_back(AddTextString("Type: Floor", game->renderer, { 0, 0, 0 }, game->screenWidth - 320, game->screenHeigth - 190, 16));
	textBuffer.push_back(AddTextString("Working Layer: 1", game->renderer, { 0, 0, 0 }, game->screenWidth - 320, game->screenHeigth - 160, 16));
	textBuffer.push_back(AddTextString("Working Layer: 2", game->renderer, { 0, 0, 0 }, game->screenWidth - 320, game->screenHeigth - 160, 16));
	textBuffer.push_back(AddTextString("Working Layer: 3", game->renderer, { 0, 0, 0 }, game->screenWidth - 320, game->screenHeigth - 160, 16));
	textBuffer.push_back(AddTextString("Zoom Level: 1x", game->renderer, { 0, 0, 0 }, game->screenWidth - 320, game->screenHeigth - 130, 16));
	textBuffer.push_back(AddTextString("Tile Page: 1", game->renderer, { 0, 0, 0 }, game->screenWidth - 320, game->screenHeigth - 100, 16));
	textBuffer.push_back(AddTextString("Working Layer: 4", game->renderer, { 0, 0, 0 }, game->screenWidth - 320, game->screenHeigth - 160, 16));
	textBuffer.push_back(AddTextString("Working Layer: 5", game->renderer, { 0, 0, 0 }, game->screenWidth - 320, game->screenHeigth - 160, 16));
}
TileMenu::textObject TileMenu::AddTextString(std::string text, SDL_Renderer* renderer, SDL_Color text_color, int posX, int posY, int fontSize)
{
	TTF_Font* Sans = TTF_OpenFont("Data/Fonts/Karmakooma.ttf", fontSize);

	SDL_Surface* surfaceMessage = TTF_RenderText_Blended(Sans, text.c_str(), text_color);

	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);


	SDL_Rect Message_rect;
	Message_rect.x = posX;
	Message_rect.y = posY;
	SDL_QueryTexture(Message, NULL, NULL, &Message_rect.w, &Message_rect.h);

	textObject obj;
	obj.text = Message;
	obj.rect = Message_rect;

	return obj;
}

void TileMenu::ChangeZoomText(GameEngine* game, std::string text)
{
	textBuffer[5] = AddTextString(text, game->renderer, { 0, 0, 0 }, game->screenWidth - 320, game->screenHeigth - 130, 16);
}

void TileMenu::ChangeTilePageText(GameEngine* game, std::string text)
{
	textBuffer[6] = AddTextString(text, game->renderer, { 0, 0, 0 }, game->screenWidth - 320, game->screenHeigth - 100, 16);
}

void TileMenu::ChangeTypeText(GameEngine* game, std::string text)
{
	textBuffer[0] = AddTextString(text, game->renderer, { 0, 0, 0 }, game->screenWidth - 320, game->screenHeigth - 190, 16);
}

void TileMenu::Draw(GameEngine* game, Map map, int selectedTile, int layer)
{
	SDL_Rect r;
	r.x = 0;
	r.y = game->screenHeigth - 205;
	r.w = game->screenWidth;
	r.h = game->screenHeigth;

	// Set render color to blue ( rect will be rendered in this color )
	SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);

	// Render rect
	SDL_RenderFillRect(game->renderer, &r);
	
	SDL_Rect rect;
	SDL_Rect rect2;
	int tileIndex = (this->tilesPerRow * nrRows)*this->viewPage;

	//SDL_RenderCopy(game->renderer, map.tilesImage[0], &rect2, &rect);
	for (int i = 0; i < this->tilesPerRow * nrRows; i++)
	{
		

		rect.x = (i*(map.getTileSize()*this->tileSize)) % (this->tilesPerRow * (map.getTileSize()*this->tileSize));
		rect.y = (game->screenHeigth - 200) + (map.getTileSize()*this->tileSize)*floor(i / this->tilesPerRow);
		rect.w = map.getTileSize()*this->tileSize;
		rect.h = map.getTileSize()*this->tileSize;
		
		

		if (i+tileIndex < map.tileList.size())
		{
			rect2.x = map.tileList[i+tileIndex].x;
			rect2.y = map.tileList[i+tileIndex].y;
			rect2.w = map.getTileSize();
			rect2.h = map.getTileSize();
		

		SDL_RenderCopy(game->renderer, map.tilesImage[0], &rect2, &rect);
		}
	}


	rect.x = game->screenWidth - 200;
	rect.y = game->screenHeigth - 200;
	rect.w = 190;
	rect.h = 190;

	rect2.x = map.tileList[selectedTile].x;
	rect2.y = map.tileList[selectedTile].y;
	rect2.w = map.getTileSize();
	rect2.h = map.getTileSize();

	SDL_RenderCopy(game->renderer, map.tilesImage[0], &rect2, &rect);
	


	ChangeTypeText(game, "Tile Type: " + to_string(map.tileList[selectedTile].w));

	SDL_RenderCopy(game->renderer, textBuffer[0].text, NULL, &textBuffer[0].rect);
	

	if (layer == 0)
	{
		SDL_RenderCopy(game->renderer, textBuffer[2].text, NULL, &textBuffer[2].rect);
	}
	if (layer == 1)
	{
		SDL_RenderCopy(game->renderer, textBuffer[3].text, NULL, &textBuffer[3].rect);
	}
	if (layer == 2)
	{
		SDL_RenderCopy(game->renderer, textBuffer[4].text, NULL, &textBuffer[4].rect);
	}

	SDL_RenderCopy(game->renderer, textBuffer[5].text, NULL, &textBuffer[5].rect);
	SDL_RenderCopy(game->renderer, textBuffer[6].text, NULL, &textBuffer[6].rect);

	if (layer == 3)
	{
		SDL_RenderCopy(game->renderer, textBuffer[7].text, NULL, &textBuffer[7].rect);
	}
	if (layer == 4)
	{
		SDL_RenderCopy(game->renderer, textBuffer[8].text, NULL, &textBuffer[8].rect);
	}
}