#include "Map.h"
#include <string>

using namespace rapidjson;
#pragma warning(disable:4996)

void Map::LoadMap(GameEngine* game)
{

	//this->tilesImage =  Load_image( "Data\\Tiles\\tiles.bmp" );
	this->readMapData(game);
}

void Map::toggleGrid()
{
	if (this->showGrid)
		this->showGrid = false;
	else
		this->showGrid = true;
}

void Map::save()
{
	Document d;
	std::string json = "{";
	
	

	json += "\"tile_width_count\":" + std::to_string(this->tiles_width_count);
	json += ",\"tile_height_count\":" + std::to_string(this->tiles_heigth_count);
	json += ",\"tile_set\" : \"Data/Tiles/Tiles.bmp\"";
	json += ",\"tile_size\" : 32,";
	
	json += "\"type_legend\": [";
	for (int i = 0; i < this->tileList.size(); i++)
	{
		json += "{";
		json += "\"type\":" + std::to_string(this->tileList[i].w);
		json += ",\"image_x\" :" + std::to_string(this->tileList[i].x);
		json += ",\"image_y\" :" + std::to_string(this->tileList[i].y);

		if (i == this->tileList.size() - 1)
			json += "}";
		else
			json += "},";
	}
	json += "],";

	//Add tiles array	
	json += "\"grid\":[";

	for (int i = 0; i < this->tiles_heigth_count; i++)
	{
		json += "[";
		for (int j = 0; j < this->tiles_width_count; j++)
		{
			json += "{\"layer\":" + std::to_string(this->mapTilePosition[i][j].layer);
			json += ",\"layer2\":" + std::to_string(this->mapTilePosition[i][j].layer2);
			json += ",\"layer3\":" + std::to_string(this->mapTilePosition[i][j].layer3);
			json += ",\"layer4\":" + std::to_string(this->mapTilePosition[i][j].layer4);
			json += ",\"type\":" + std::to_string(this->mapTilePosition[i][j].blockid);


			if (j == this->tiles_heigth_count - 1)
				json += "}";
			else
				json += "},";
		}

		if (i == this->tiles_heigth_count-1)
			json += "]";
		else
			json += "],";
	}

	json += "]";

	json += "}";
	d.Parse(json.c_str());
	// ...
	FILE* fp = fopen("Data/Tiles/map.json", "wb"); // non-Windows use "w"
	char writeBuffer[65536];
	FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
	Writer<FileWriteStream> writer(os);
	d.Accept(writer);
	fclose(fp);
}

void Map::readMapData(GameEngine* game)
{
	//Read map file
	//  ifstream ifs;
	string map_path = "Data/Tiles/map.json";
	ifstream ifs(map_path.c_str(), ifstream::binary);

	std::filebuf* pbuf = ifs.rdbuf();

	std::size_t size = pbuf->pubseekoff(0, ifs.end, ifs.in);
	pbuf->pubseekpos(0, ifs.in);


	char* buffer = new char[size]();
	*buffer = '\0';

	pbuf->sgetn(buffer, size);

	ifs.close();

	//####### Windows only!
	string s = string(buffer);
	s = s.substr(0, size);

	//Parse map
	Document document;
	document.Parse(s.c_str());
	//####### Windows only!

	//####### Linux only!
	//Document document;
	//document.Parse(buffer);
	//####### Linux only!

	//clean up buffer
	delete[] buffer;

	if (document.IsObject())
	{
		Tile tile;
		int count = 0;



		//Check json objects
		if (!document.HasMember("tile_set"))
		{
			cout << "failed to load map! member: tile_set not found\n";
			return;
		}
		else if (!document["tile_set"].IsString())
		{
			cout << "failed to load map! member: tile_set is not a string\n";
			return;
		}

		if (!document.HasMember("tile_size"))
		{
			cout << "failed to load map! member: tile_size not found\n";
			return;
		}
		else if (!document["tile_size"].IsInt())
		{
			cout << "failed to load map! member: tile_size is not an integer\n";
			return;
		}

		/*    if(!document.HasMember("tile_count"))
		{
		cout << "failed to load map! member: tile_count not found\n";
		return;
		}
		else if(!document["tile_count"].IsInt())
		{
		cout << "failed to load map! member: tile_count is not an integer\n";
		return;
		}*/

		if (!document.HasMember("grid"))
		{
			cout << "failed to load map! member: grid not found\n";
			return;
		}
		else if (!document["grid"].IsArray())
		{
			cout << "failed to load map! member: grid is not an array\n";
			return;
		}

		//load json objects
		string tile_set = document["tile_set"].GetString();
		this->tile_size = document["tile_size"].GetInt();
		this->tiles_width_count = document["tile_width_count"].GetInt();
		this->tiles_heigth_count = document["tile_height_count"].GetInt();
		this->tilesImage[0] = Load_image(tile_set, game);

		const Value& a = document["grid"];
		// assert(a.IsArray());

		for (int i = 0; i < document["type_legend"].Size(); i++)
		{
			SDL_Rect rect;
			rect.x = document["type_legend"][i]["image_x"].GetInt();
			rect.y = document["type_legend"][i]["image_y"].GetInt();
			rect.w = document["type_legend"][i]["type"].GetInt();
			tileList.push_back(rect);
		}

		mapTilePosition = new Tile*[this->tiles_width_count];

		for (SizeType i = 0; i < a.Size(); i++)
		{
			mapTilePosition[i] = new Tile[this->tiles_heigth_count];

			if (a[i].IsArray())
			{
				for (SizeType j = 0; j < a[i].Size(); j++)
				{
					if (!a[i][j].HasMember("type"))
					{
						cout << "failed to load map! tile misses members\n";
						return;
					}
					else if (!a[i][j]["type"].IsInt())
					{
						cout << "failed to load map! tiles members is not correct format\n";
						return;
					}

					int type_id = a[i][j]["type"].GetInt();
					int type_id_layer = a[i][j]["layer"].GetInt();
					int type_id_layer2 = a[i][j]["layer2"].GetInt();
					int type_id_layer3 = a[i][j]["layer3"].GetInt();
					int type_id_layer4 = a[i][j]["layer4"].GetInt();

					if (!document["type_legend"][type_id].HasMember("image_x") || !document["type_legend"][type_id].HasMember("image_y"))
					{
						cout << "failed to load map! tile misses members\n";
						return;
					}
					else if (!document["type_legend"][type_id]["image_x"].IsInt() || !document["type_legend"][type_id]["image_y"].IsInt())
					{
						cout << "failed to load map! tiles members is not correct format\n";
						return;
					}

					tile.worldPosition.x = j*tile_size;
					tile.worldPosition.y = i*tile_size;
					tile.imagePosition.x = document["type_legend"][type_id]["image_x"].GetInt();
					tile.imagePosition.y = document["type_legend"][type_id]["image_y"].GetInt();
					tile.type = 0;
					tile.blockid = type_id;
					tile.layer = type_id_layer;
					tile.layer2 = type_id_layer2;
					tile.layer3 = type_id_layer3;
					tile.layer4 = type_id_layer4;
					tile.boundingBoxType = 0;
					mapTilePosition[i][j] = tile;
					//count++;
				}
			}
			else
			{
				cout << "failed to load map! could not read tile list\n";
				return;
			}
		}

		for (SizeType i = a.Size(); i < this->tiles_width_count; i++)
		{
			mapTilePosition[i] = new Tile[this->tiles_heigth_count];

			for (SizeType j = 0; j < this->tiles_heigth_count; j++)
			{
				tile.worldPosition.x = j*tile_size;
				tile.worldPosition.y = i*tile_size;
				tile.imagePosition.x = 0;
				tile.imagePosition.y = 0;
				tile.type = 0;
				tile.blockid = 0;
				tile.layer = -1;
				tile.layer2 = -1;
				tile.layer3 = -1;
				tile.layer4 = -1;
				tile.boundingBoxType = 0;
				mapTilePosition[i][j] = tile;
			}
		}

	}
	else
	{
		cout << "failed to load map: not a correct json file\n";
	}

}

void Map::ShowLayer(int layer)
{
	if (layer == -1 || layer == 0 || layer == 1 || layer == 2 )
		this->displayLayer = layer;

}
void Map::Draw(GameEngine* game)
{
	SDL_Rect rect;
	SDL_Rect rect2;

	//Calculate where the camera is in the matrice
	int num_t_x = floor((game->screenWidth / this->tile_size)); //* game->camera.getZoomLevel());
		int num_t_y = floor((game->screenHeigth / this->tile_size)); //* game->camera.getZoomLevel());

	//get Y start postion
	int render_y_start = floor(game->camera.getYPosition()*-1 / this->tile_size)/game->camera.getZoomLevel();
	render_y_start = (render_y_start < 0) ? 0 : render_y_start;
	render_y_start = (render_y_start > this->tiles_heigth_count) ? this->tiles_heigth_count : render_y_start;

	//get Y END postion
	int render_y_end = (floor(game->camera.getYPosition()*-1 / this->tile_size) + num_t_y / (game->camera.getZoomLevel()))+1;
	render_y_end = (render_y_end < 0) ? 0 : render_y_end;
	render_y_end = (render_y_end > this->tiles_heigth_count) ? this->tiles_heigth_count : render_y_end;

	//get X start postion
	int render_x_start = floor(game->camera.getXPosition()*-1 / this->tile_size) / game->camera.getZoomLevel();
	render_x_start = (render_x_start < 0) ? 0 : render_x_start;
	render_x_start = (render_x_start > this->tiles_width_count) ? this->tiles_width_count : render_x_start;

	//get X end postion
	int render_x_end = (floor(game->camera.getXPosition()*-1 / this->tile_size) + num_t_x / (game->camera.getZoomLevel()))+1;
	render_x_end = (render_x_end < 0) ? 0 : render_x_end;
	render_x_end = (render_x_end > this->tiles_width_count) ? this->tiles_width_count : render_x_end;


	//Render all tiles on screen
	for (int y = render_y_start; y < render_y_end; y++)
	{
		for (int x = render_x_start; x < render_x_end; x++)
		{
			if (this->showGrid)
			{
				rect.x = (this->mapTilePosition[y][x].worldPosition.x + x)*game->camera.getZoomLevel() + game->camera.getXPosition();
				rect.y = (this->mapTilePosition[y][x].worldPosition.y + y)*game->camera.getZoomLevel() + game->camera.getYPosition();
			}
			else
			{
				rect.x = (this->mapTilePosition[y][x].worldPosition.x)*game->camera.getZoomLevel() + game->camera.getXPosition();
				rect.y = (this->mapTilePosition[y][x].worldPosition.y)*game->camera.getZoomLevel() + game->camera.getYPosition();
			}

			rect.w = this->tile_size*game->camera.getZoomLevel();

			rect.h = this->tile_size*game->camera.getZoomLevel();



			rect2.x = this->tileList[mapTilePosition[y][x].blockid].x;

			rect2.y = this->tileList[mapTilePosition[y][x].blockid].y;

			rect2.w = this->tile_size;

			rect2.h = this->tile_size;

			if (this->displayLayer == -1 || this->displayLayer == 0)
				SDL_RenderCopy(game->renderer, this->tilesImage[mapTilePosition[y][x].type], &rect2, &rect);

			if (mapTilePosition[y][x].layer != -1 && (this->displayLayer == -1 || this->displayLayer == 1))
			{
				rect2.x = this->tileList[mapTilePosition[y][x].layer].x;

				rect2.y = this->tileList[mapTilePosition[y][x].layer].y;
				SDL_RenderCopy(game->renderer, this->tilesImage[mapTilePosition[y][x].type], &rect2, &rect);
			}

			if (mapTilePosition[y][x].layer2 != -1 && (this->displayLayer == -1 || this->displayLayer == 2))
			{
				rect2.x = this->tileList[mapTilePosition[y][x].layer2].x;

				rect2.y = this->tileList[mapTilePosition[y][x].layer2].y;
				SDL_RenderCopy(game->renderer, this->tilesImage[mapTilePosition[y][x].type], &rect2, &rect);
			}
			if (mapTilePosition[y][x].layer3 != -1 && (this->displayLayer == -1 || this->displayLayer == 3))
			{
				rect2.x = this->tileList[mapTilePosition[y][x].layer3].x;

				rect2.y = this->tileList[mapTilePosition[y][x].layer3].y;
				SDL_RenderCopy(game->renderer, this->tilesImage[mapTilePosition[y][x].type], &rect2, &rect);
			}
			if (mapTilePosition[y][x].layer4 != -1 && (this->displayLayer == -1 || this->displayLayer == 4))
			{
				rect2.x = this->tileList[mapTilePosition[y][x].layer4].x;

				rect2.y = this->tileList[mapTilePosition[y][x].layer4].y;
				SDL_RenderCopy(game->renderer, this->tilesImage[mapTilePosition[y][x].type], &rect2, &rect);
			}
		}
	}
}

SDL_Texture *Map::Load_image(string filename, GameEngine* game)
{
	SDL_Surface* loaded_image = NULL;

	if (filename.c_str() == NULL)
	{
		return NULL;
	}

	loaded_image = SDL_LoadBMP(filename.c_str());

	if (loaded_image == NULL)
	{
		return NULL;
	}

	Uint32 colorkey = SDL_MapRGB(loaded_image->format, 255, 0, 255);

	SDL_SetColorKey(loaded_image, SDL_RLEACCEL | SDL_TRUE, colorkey);


	SDL_Texture *bitmapTex = SDL_CreateTextureFromSurface(game->renderer, loaded_image);

	SDL_FreeSurface(loaded_image);
	return bitmapTex;
}
void Map::ChangeTileType(int tile)
{
	
	if (this->tileList[tile].w <= 10)
		this->tileList[tile].w++;

	if (this->tileList[tile].w > 10)
		this->tileList[tile].w = 0;
}

void Map::RemoveLayer(GameEngine* game, int x, int y, int layer)
{
	int mXpos = ((game->camera.getXPosition()*-1) + x) / game->camera.getZoomLevel();
	int mYpos = ((game->camera.getYPosition()*-1) + y) / game->camera.getZoomLevel();

	int gridXpos;
	int gridYpos;

	if (this->showGrid)
	{
		gridXpos = mXpos / (this->tile_size + 1);
		gridYpos = mYpos / (this->tile_size + 1);
	}
	else
	{
		gridXpos = mXpos / this->tile_size;
		gridYpos = mYpos / this->tile_size;
	}

	if (layer == 1)
		this->mapTilePosition[gridYpos][gridXpos].layer = -1;
	if (layer == 2)
		this->mapTilePosition[gridYpos][gridXpos].layer2 = -1;
	if (layer == 3)
		this->mapTilePosition[gridYpos][gridXpos].layer3 = -1;
	if (layer == 4)
		this->mapTilePosition[gridYpos][gridXpos].layer4 = -1;

}

void Map::ChangeTile(GameEngine* game, int mousePosX, int mousePosY, int tile, int layer)
{
	int mXpos = ((game->camera.getXPosition()*-1) + mousePosX) / game->camera.getZoomLevel();
	int mYpos = ((game->camera.getYPosition()*-1) + mousePosY) / game->camera.getZoomLevel();

	int gridXpos;
	int gridYpos;

	if (this->showGrid)
	{
		gridXpos = mXpos / (this->tile_size+1);
		gridYpos = mYpos / (this->tile_size+1);
	}
	else
	{
		gridXpos = mXpos / this->tile_size;
		gridYpos = mYpos / this->tile_size;
	}

	//this->mapTilePosition[gridYpos][gridXpos].imagePosition.x = this->tileList[tile].x;
	//this->mapTilePosition[gridYpos][gridXpos].imagePosition.y = this->tileList[tile].y;

	if (layer == 0)
		this->mapTilePosition[gridYpos][gridXpos].blockid = tile;
	if (layer == 1)
		this->mapTilePosition[gridYpos][gridXpos].layer = tile;
	if (layer == 2)
		this->mapTilePosition[gridYpos][gridXpos].layer2 = tile;
	if (layer == 3)
		this->mapTilePosition[gridYpos][gridXpos].layer3 = tile;
	if (layer == 4)
		this->mapTilePosition[gridYpos][gridXpos].layer4 = tile;

}

int Map::getTileSize()
{
	return this->tile_size;

}