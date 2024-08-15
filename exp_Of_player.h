#pragma once
#include"Components.h"
#include "Game.h"
#include"TextureManager.h"

class exp_Of_player : public Component
{
private:

	int tmp;
	SDL_Rect srcRect, destRect;
	std::string path;
	SDL_Texture* tex;
	TransformComponent* transform;

public:
	int lv;
	int maxExp;
	int exp;
	bool lvup = 0;
	exp_Of_player(std::string path)
	{
		this->path = path;
		exp = 0;
		lv = 1;
	}
	void init() override
	{
		maxExp = 100;
		tex = texturemanager::LoadTexture(path.c_str());
		srcRect.x = srcRect.y = 0;
		srcRect.w = srcRect.h = 32;
		destRect.x = 0;
		destRect.y = 0;
		transform = &entity->getComponent<TransformComponent>();

	}
	void up()
	{
		exp += 50;
		if (exp >= maxExp)
		{
			lv += 1;
			exp = 0;
			lvup = 1;
			maxExp += 150;
		}
		
	}
	void update() override
	{
		destRect.w = double(1.0*exp/maxExp)*1280;
		destRect.h = 16;
	}
	void draw() override
	{
		texturemanager::Draw(tex, srcRect, destRect);
		int a = (Game::clock / 1000);
		int b = a/60;
		std::string tmp = std::to_string(b) + " : " + std::to_string(a%60);
		SDL_Rect dest = { 650,50,60,25 };
		SDL_Color color = { 255,255,255 };
		SDL_Texture* tex = texturemanager::LoadTextureFromFont("fonts/KO.ttf", color, tmp.c_str());
		texturemanager::write(tex, dest);
		SDL_DestroyTexture(tex);
	}

	int getlv()
	{
		return lv;
	}
};