#pragma once
#include"ECS.h"
#include<ctime>
#include"TextureManager.h"



class EnemyComponents
{
private:
	int xpos;
	int ypos;
	const char* path;
	SDL_Rect src, des;
	SDL_Texture* tex;
	Entity enemies;
public:
	EnemyComponents(int a, const char* path)
	{
		this->path = path;
		srand(time(0));

	}

	void SpawnPosition()
	{
		xpos = rand() % 700;
		ypos = rand() % 500;
	}


	void update()
	{
		des.x = xpos;
		des.y = ypos;
		des.w = 32;
		des.h = 32;
		src.x = src.y = 0;
		src.w = src.h = 32;
	}

	void draw()
	{
		tex = texturemanager::LoadTexture(path);
		texturemanager::Draw(tex, src, des);
	}



};