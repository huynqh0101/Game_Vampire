#pragma once
#include"Game.h"
#include"TextureManager.h"
#include"Components.h"
#include<fstream>
#include<cstring>

class Map
{
public:
	Map() = default;
	~Map();
	Map(std::string filepath);
	void LoadMap(int arr[120][150]);
	void DrawMap();
	TransformComponent* transform;


	SDL_Rect src, dest;
	int delta_x,delta_y;
	SDL_Texture* tex1;
	SDL_Texture* tex2;
	SDL_Texture* tex3;
	SDL_Texture* tex4;
	SDL_Texture* tex5;
	SDL_Texture* tex6;
	SDL_Texture* tex7;
	SDL_Texture* tex8;
	SDL_Texture* tex9;
	SDL_Texture* tex10;
	SDL_Texture* tex11;
	SDL_Texture* tex12;
	SDL_Texture* tex13;
	SDL_Texture* tex14;
	SDL_Texture* tex15;


	int map[120][150];
	 
};