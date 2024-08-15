#pragma once
#include"Components.h"
#include "Game.h"
#include<SDL_keyboard.h>


class KeyBoardController : public Component
{
public:
	TransformComponent* transform;
	SpriteComponent* sprite;
	int speed = 1;
	const Uint8* keyboadstate = SDL_GetKeyboardState(NULL);

	void init() override
	{
		
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
		
	}

	void update() override
	{
		if (Game::event.type == SDL_KEYUP|| (!keyboadstate[SDL_SCANCODE_A] &&! keyboadstate[SDL_SCANCODE_D] && !keyboadstate[SDL_SCANCODE_W] &&! keyboadstate[SDL_SCANCODE_S])) {
			sprite->animated = 0;
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				transform->velocity.y = 0;
				transform->veloc_of_map.y = 0;
				break;
			case SDLK_s:
				transform->velocity.y = 0;
				transform->veloc_of_map.y = 0;
				break;
			case SDLK_a:
				//sprite->spriteflip = SDL_FLIP_NONE;
				transform->velocity.x = 0;
				transform->veloc_of_map.x = 0;
				break;
			case SDLK_d:
				//sprite->spriteflip = SDL_FLIP_NONE;
				transform->velocity.x = 0;
				transform->veloc_of_map.x = 0;
				break;
			default:
				break;
			}
		}
		else if (Game::event.type == SDL_KEYDOWN || keyboadstate[SDL_SCANCODE_A] || keyboadstate[SDL_SCANCODE_D] || keyboadstate[SDL_SCANCODE_W] || keyboadstate[SDL_SCANCODE_S]) {
			sprite->animated = 1;
			if (transform->position.y < 10 || transform->position.y>750) transform->velocity.y = 0;
			else  if (transform->velocity.y != 0 && transform->veloc_of_map.y == 0 && transform->position.y > 400)
			{
				transform->velocity.y = 0;
				transform->veloc_of_map.y = speed;
			}
			if (transform->position.x < 30 || transform->position.x>1200) transform->velocity.x = 0;

			if (transform->videomap.y < 65 || transform->videomap.y>1500)
			{
				transform->veloc_of_map.y = 0;
			}
			if (transform->videomap.x < 500 || transform->videomap.x>2500)
			{
				transform->veloc_of_map.x = 0;

			}
			if (Game::event.key.keysym.sym == SDLK_w || keyboadstate[SDL_SCANCODE_W])
			{
				if ((transform->videomap.y <= 64) || transform->position.y > 450)
				{
					if (transform->position.y < 10) transform->velocity.y = 0;
					else
					{
						transform->velocity.y = -1 * speed;
					}
					transform->veloc_of_map.y = 0;

				}
				else
				{
					transform->velocity.y = 0;
					transform->veloc_of_map.y = -1 * speed;
				}
			}
			else if (Game::event.key.keysym.sym == SDLK_d || keyboadstate[SDL_SCANCODE_D])
			{
				if (sprite->spriteflip == SDL_FLIP_HORIZONTAL)
					sprite->spriteflip = SDL_FLIP_NONE;
				if (transform->videomap.x >= 2500 || transform->position.x < 500)
				{
					
					if (transform->position.x > 1200) transform->velocity.x = 0;
					else
						transform->velocity.x = speed;
					transform->veloc_of_map.x = 0;
				}
				else

				{
					transform->velocity.x = 0;
					transform->veloc_of_map.x = speed;
				}
			}
			else  if (Game::event.key.keysym.sym == SDLK_a || keyboadstate[SDL_SCANCODE_A])
			{

				if (transform->videomap.x <= 500 || transform->position.x > 500)
				{
					
					sprite->spriteflip = SDL_FLIP_HORIZONTAL;
					if (transform->position.x < 30) transform->velocity.x = 0;
					else
						transform->velocity.x = -1 * speed;
					transform->veloc_of_map.x = 0;

				}
				else
				{
					sprite->spriteflip = SDL_FLIP_HORIZONTAL;
					transform->velocity.x = 0;
					transform->veloc_of_map.x = -1 * speed;

				}
			}
			 if (Game::event.key.keysym.sym == SDLK_s || keyboadstate[SDL_SCANCODE_S])
			{
				if (transform->videomap.y >= 1400 || transform->position.y < 450)
				{
					if (transform->position.y > 750) transform->velocity.y = 0;
					else
						transform->velocity.y = speed;
					transform->veloc_of_map.y = 0;
				}
				else
				{
					transform->velocity.y = 0;
					transform->veloc_of_map.y = speed;
				}
			}
			

		}
	}
};

