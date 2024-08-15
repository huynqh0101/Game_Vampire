#pragma once
#include"Components.h"
#include"Game.h"
class LifeOfEntiy : public Component
{

public:
	int hp;
	LifeOfEntiy(int HP)
	{
		hp = HP;
	}
	void init() override
	{
		
	}

	void update() override
	{
		
	}

	
};