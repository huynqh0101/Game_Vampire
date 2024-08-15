#pragma once
#include"ECS.h"
#include"Components.h"
#include"EnemyComponents.h"

class Enemies : public Component
{
private:
	int xpos;
	int ypos;
	std::vector<EnemyComponents> enemies;

public:
	Enemies()
	{
		
	}
};