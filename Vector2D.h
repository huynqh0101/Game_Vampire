#pragma once
#include"Game.h"
class Vector2D
{public:
	float x;
	float y;
	Vector2D();
	Vector2D(float x, float y);


	Vector2D& Add(const Vector2D& vec);
	Vector2D& Subtract(const Vector2D& vec);
};