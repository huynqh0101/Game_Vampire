#pragma once
#include"Components.h"
#include"Game.h"
class LifeOfPlayer : public Component
{
private:
	TransformComponent* transform;
	SDL_Rect srcRect, desRect;
	SDL_Texture* tex;
	SDL_Texture* tex1;
	
	

public:

	int hp;
	int maxhp;
	bool loss_HP = 0;
	int life;

	LifeOfPlayer(int HP)
	{
		maxhp = hp = HP;
		life = 2;
	}
	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		tex = texturemanager::LoadTexture("hp.png");
		tex1 = texturemanager::LoadTexture("redborder3.png");
		srcRect.x = srcRect.y = 0;
		srcRect.w = srcRect.h = 32;

	}

	void update() override
	{
		desRect.x = transform->position.x;
		desRect.y = transform->position.y + 70;
		desRect.h = 10;
		desRect.w = double(1.0*hp/maxhp)*100;
	}

	void draw() override
	{
		
		texturemanager::Draw(tex, srcRect, desRect);
		if (loss_HP)
		{
			SDL_RenderCopy(Game::renderer, tex1, NULL, NULL);
		}
	}

	
};