#pragma once
#include"Components.h"
#include<string>
#include"Collision.h"

class ColliderComponent : public  Component

{
public:
	SDL_Rect rec;
	std::string tag;
	TransformComponent* transform;

	ColliderComponent(std::string t)
	{
		tag = t;
	}

	void init() override
	{
		if (!entity->hasComponent<TransformComponent>())
		{
			entity->addComponent<TransformComponent>();
		}
		transform = &entity->getComponent<TransformComponent>();
	}

	void update() override
	{
		rec.x = static_cast<int> (transform->position.x);
		rec.y = static_cast<int> (transform->position.y);
		rec.w = transform->width*transform->scale;
		rec.h = transform->height*transform->scale;

	}


};
