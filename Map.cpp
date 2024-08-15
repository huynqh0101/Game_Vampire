#include"Map.h"
#include"Game.h"
#include"TextureManager.h"
#include<fstream>
#include<cstring>


int lv1[120][150];

Map::Map(std::string filepath)
{
	std::fstream file(filepath);
	int n;
	for(int i = 0; i < 120; i++)
		for (int j = 0; j < 150;j++)
		{
			file >> n;
			lv1[i][j] = n;
			
		}
	tex1 = texturemanager::LoadTexture("tileset/hoa/5.png");
	tex2 = texturemanager::LoadTexture("tileset/hoa/6.png");
	tex3 = texturemanager::LoadTexture("tileset/hoa/7.png");
	tex4 = texturemanager::LoadTexture("tileset/hoa/3.png");
	tex5 = texturemanager::LoadTexture("tileset/hoa/1.png");
	tex6 = texturemanager::LoadTexture("tileset/hoa/2.png");
	tex7 = texturemanager::LoadTexture("tileset/hoa/4.png");
	tex8 = texturemanager::LoadTexture("tileset/hoa/8.png");
	LoadMap(lv1);
	src.x = 0;
	src.y = 0;
	src.w = src.h = 32;
	dest.w = dest.h = 32;
}



//Map::Map() {
//	
//	tex1 = texturemanager::LoadTexture("grass_1.png");
//	tex2 = texturemanager::LoadTexture("grass_2.png");
//	tex3 = texturemanager::LoadTexture("grass_3.png");
//	LoadMap(lv1);
//
//	src.x = src.y = 0;
//	src.w = src.h = 32;
//	dest.w = dest.h = 32;
//
//}

Map::~Map()
{
	SDL_DestroyTexture(tex1);
	SDL_DestroyTexture(tex2);
	SDL_DestroyTexture(tex3);
	SDL_DestroyTexture(tex4);
	SDL_DestroyTexture(tex5);
	SDL_DestroyTexture(tex6);
	SDL_DestroyTexture(tex7);
	SDL_DestroyTexture(tex8);
	SDL_DestroyTexture(tex9);
	SDL_DestroyTexture(tex10);
	SDL_DestroyTexture(tex11);
	SDL_DestroyTexture(tex12);
	SDL_DestroyTexture(tex13);
	SDL_DestroyTexture(tex14);
	SDL_DestroyTexture(tex15);
}

void Map::LoadMap(int lv1[120][150])
{
	for (int i = 0; i < 120; i++)
	{
		for (int j = 0; j < 150; j++)
		{
			map[i][j] = lv1[i][j];
		}
	}
}
void Map::DrawMap()
{
	for (int i = 0; i < 120; i++)
	{
		for (int j = 0; j < 150; j++)
		{
			int type = map[i][j];
			dest.x = j * 32+delta_x-200;
			dest.y = i * 32+delta_y-300;
			switch (type)
			{
			case 1: {
				texturemanager::Draw(tex1, src, dest);
				break;
			}
			case 2: {
				texturemanager::Draw(tex2, src, dest);
				break;
			}
			case 3: {
				texturemanager::Draw(tex3, src, dest);
				break;
			}
			case 4: {
				texturemanager::Draw(tex4, src, dest);
				break;
			}
			case 5:
				texturemanager::Draw(tex5, src, dest);
				break;
			case 6:
				texturemanager::Draw(tex6, src, dest);
				break;
			case 7: {
				texturemanager::Draw(tex7, src, dest);
				break;
			}
			case 8: {
				texturemanager::Draw(tex8, src, dest);
				break;
			}
			default:
				/*texturemanager::Draw(tex2, src, dest);*/
				break;
			}
		}
	}
}