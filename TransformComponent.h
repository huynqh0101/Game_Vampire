#pragma once
#include"ECS.h"
#include"Vector2D.h"

class TransformComponent : public Component
{

public:
	Vector2D position;
	Vector2D velocity;
	Vector2D videomap;
	Vector2D veloc_of_map;

	int width = 64;
	int height = 64;
	int scale = 1;
	int speed = 10;
	bool isInRange = 0;
	TransformComponent()
	{

		position.x = videomap.x = 0.0f;
		position.y = videomap.x = 0.0f;
	}
	TransformComponent(float x, float y) {
		position.x = videomap.x = x ;
		position.y = videomap.y = y ;
	}
	TransformComponent(float x, float y, int w, int h, int sc) {
		position.x = x;
		position.y = y;
		width = w;
		height = h;
		scale = sc;
	}

	void init() override
	{
		velocity.x = 0;
		velocity.y = 0;
	}

	
	void update() override
	{
		/*if (position.x > 800)
		{
			velocity.x = -1;
		}*/
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
		videomap.x += veloc_of_map.x * speed;
		videomap.y += veloc_of_map.y * speed;
	}
	
	
};