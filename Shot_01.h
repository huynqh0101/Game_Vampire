#pragma once
#include"Components.h"
#include<vector>
#include"projectiles.h"
#include"Collision.h"
#include<cmath>
#include<SDL_mixer.h>


class shot01 : public Component
{

public:
	Mix_Chunk* sound = NULL;
	int reload = 1500;//time to reload the bullet
	TransformComponent* transform;
	SpriteComponent* sprites;
	std::vector<std::unique_ptr<CreateProjectiles>> projectiles;
	int i = 1;
	int ammount = 1;
	int veloc = 45;
	int damage = 30;
	
	shot01() = default;
	~shot01()
	{
		Mix_FreeChunk(sound);
	}

	void init() override
	{
		sprites = &entity->getComponent<SpriteComponent>();
		transform = &entity->getComponent<TransformComponent>();
		sound = Mix_LoadWAV("sound/VS_Projectile_v06-02.ogg");
		if (sound == NULL) std::cout << "NULL";
	}

	void update() override
	{
		long long a = (Game::clock) / reload;


		if (a >= i)
		{
			int tmp = 0;
			for (int j = 0;j < ammount; j++)
			{

				CreateProjectiles* bullet = new CreateProjectiles(31,8,"BowieKnife.png",5);
				bullet->init();
				bullet->xpos = static_cast<int>(transform->position.x)+tmp;
				bullet->ypos = static_cast<int>(transform->position.y)+tmp;
				bullet->dir = sprites->spriteflip == SDL_FLIP_HORIZONTAL ? -1 : 1;
				bullet->update();
			
				projectiles.emplace_back(std::move(bullet));
				tmp += 5;
			}
			i = i + 1;
		}
			
		
	}

	void draw() override
	{
		
		for (auto& c : projectiles)
		{
			if (c->des.x == transform->position.x+30)
			{
				Mix_PlayChannel(-1, sound, 0);
			}
			c->draw();
			c->des.x += veloc * c->dir - transform->veloc_of_map.x*transform->speed;
			c->des.y -= transform->veloc_of_map.y * transform->speed;
			c->tail_des.x += veloc * c->dir - transform->veloc_of_map.x * transform->speed;
			c->tail_des.y -= transform->veloc_of_map.y * transform->speed;
		}
		for (int i = 0; i < projectiles.size(); i++)
			if (projectiles[i]->des.x > 1280||projectiles[i]->des.y > 900||projectiles[i]->des.x<0||projectiles[i]->des.y<0||projectiles[i]->coll == 1) projectiles.erase(projectiles.begin() + i);
	}
	
};