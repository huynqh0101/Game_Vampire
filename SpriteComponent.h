#pragma once
#include"Components.h"
#include"TextureManager.h"
#include"SDL.h"

class SpriteComponent : public Component
{
public:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, desRect;

	
	int frames = 0;
	int speed = 100;
	bool animated = 0;

	SDL_RendererFlip spriteflip = SDL_FLIP_NONE;
	SpriteComponent() = default;
	SpriteComponent(const char* path,int srcw, int srch)
	{
		SetText(path);
		srcRect.w = srcw;
		srcRect.h = srch;
	}
	SpriteComponent(const char* path,int mframes, int mspeed,bool animate,int srcw,int srch)
	{
		srcRect.w = srcw;
		srcRect.h = srch;
		animated = animate;
		frames = mframes;
		speed = mspeed;
		SetText(path);
	}
	~SpriteComponent()
	{
		SDL_DestroyTexture(texture);
	}
	void SetText(const char* path)
	{
		texture = texturemanager::LoadTexture(path);
	}
	void init() override
	{
		
		transform = &entity->getComponent<TransformComponent>();
	
		srcRect.x = srcRect.y = 0;
		
	}

	void update() override
	{
		if (animated)
		{
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}
		else srcRect.x = srcRect.y = 0;
		desRect.x = static_cast<int>(transform->position.x);
		desRect.y = static_cast<int>(transform->position.y);
		desRect.w = transform->width * transform->scale;
		desRect.h = transform->height * transform->scale;
	}

	void draw() override
	{
		texturemanager::draw(texture, srcRect, desRect,spriteflip);
	}
};