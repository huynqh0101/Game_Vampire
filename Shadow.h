#pragma once
#include"Components.h"
#include"Game.h"
#include"TextureManager.h"
#include<vector>
#include"projectiles.h"

class Shadow :public Component
{
private:
	TransformComponent* transform;
	SpriteComponent* sprite;
	SDL_Texture* tex;
	SDL_Texture* tex2;
	SDL_Rect src, des,des2;
public:
	Shadow()
	{
		
	};

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
		des.x = transform->position.x - 20;
		des.y = transform->position.y+64;
		des2.x = transform->position.x - 40;
		des2.y = transform->position.y + 64;
		
		tex = texturemanager::LoadTexture("tail.png");
		tex2 = texturemanager::LoadTexture("tail.png");
		src.x = src.y = 0;
		src.w = 400;
		src.h = 400;
		des.w = 45;
		des.h = 45;
		des2.w = des2.h = 30;

		
	}

	void update() override
	{
		des.x -= transform->veloc_of_map.x*transform->speed;
		des.y -= transform->veloc_of_map.y*transform->speed;
		des2.x -= transform->veloc_of_map.x * transform->speed;
		des2.y -= transform->veloc_of_map.y * transform->speed;
		
		if (sprite->animated == 1)
		{
			des.w-=3;
			des.h-=3;
			des2.w -= 2;
			des2.h -= 2;
		}
		if (des.w == 0)
		{
			des.w = des.h = 45;
			
			des.x = transform->position.x + (sprite->spriteflip == SDL_FLIP_HORIZONTAL ? 70:-20);
			des.y = transform->position.y+64;
			
		}
		if (des2.w == 0)
		{
			des2.w = des2.h = 30;
			des2.x = transform->position.x + (sprite->spriteflip == SDL_FLIP_HORIZONTAL ? 90 : -40);
			des2.y = transform->position.y + 64;
		}
	}

	void draw() override
	{
		if (sprite->animated)
		{
			texturemanager::Draw(tex, src, des);
			texturemanager::Draw(tex2, src, des2);
		}
		
	}
};