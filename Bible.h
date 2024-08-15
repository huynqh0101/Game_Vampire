#pragma once
#include"Game.h"
#include"TextureManager.h"
#include"Components.h"

class Bible
{
public:
	SDL_Rect src, des;
	SDL_Texture* tex;
	SDL_Texture* tex2;

	int xpos, ypos;
	int Rad =200;
	int first_phi;

	Bible(int w, int h)
	{
		src.w = w;
		src.h = h;
	};

	void init()
	{
		tex = texturemanager::LoadTexture("UI/Bible.png");
		

		src.x = src.y = 0;
		des.w = des.h = 30;
	}


	void update()
	{
		des.x = xpos;
		des.y = ypos;
		
	}

	void draw()
	{
		texturemanager::Draw(tex, src, des);
	}
	
	

};