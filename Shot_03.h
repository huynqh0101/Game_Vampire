#pragma once
#include"Game.h"
#include"TextureManager.h"
#include"Components.h"

class Shot_03 :public Component
{
private:
	SDL_Texture* tex;
	TransformComponent* transform;
	SDL_Rect src, des;

public:
	int range = 0;
	int coolTime;
	int damage = 2;
	Shot_03()
	{};

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		tex = texturemanager::LoadTexture("store_photo/vfx.png");
		src.x = src.y = 0;
		src.w = src.h = 246;
		des.w = des.h = range * 2;
		coolTime = 2;
	}

	void update() override
	{
		des.w = des.h = range * 2;
		des.x = transform->position.x+32-range;
		des.y = transform->position.y+32-range;
	}

	int xCenter()
	{
		return transform->position.x + 32;
	}
	int yCenter()
	{
		return transform->position.y + 32;
	}

	int getRange()
	{
		return range;
	}

	bool cooldown()
	{
		return (Game::clock / 1000) % coolTime == 0;
	}

	void upgrade()
	{
		if (range == 0)
		{
			range += 150;
		}
		else
		range += 20;
	}
	void draw() override
	{
		texturemanager::Draw(tex, src, des);
	}
};