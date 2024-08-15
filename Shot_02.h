#pragma once
#include"Game.h"
#include"TextureManager.h"
#include"Components.h"
#include"Bible.h"
#include<vector>
#include<cmath>

class Shot_02 : public Component
{
public:
	TransformComponent* transfrom;
	std::vector<std::unique_ptr<Bible>> book;
	int amount;
	int first_phi = 0;
	int cooldown;
	int exist;
	int damage = 10;
	float speed = 0.002;

	Shot_02()
	{};

	void init() override
	{
		transfrom = &entity->getComponent<TransformComponent>();
		amount = 0;
		cooldown = 20;
		exist = cooldown / 3;
	}

	void update() override
	{
		if ((Game::clock / 1000) % cooldown <= exist)
		{
			while (book.size()<amount)
			{
				Bible* bible = new Bible(78, 119);
				bible->init();
				bible->xpos = transfrom->position.x + bible->Rad;
				bible->ypos = transfrom->position.y + bible->Rad;
				first_phi += (2*M_PI)/amount;
				bible->first_phi = this->first_phi;
				book.emplace_back(std::move(bible));
			}
		}
		else for (int i = 0; i < book.size(); i++)
		{
			
			book.erase(book.begin() + i);

		}
	}

	void draw() override
	{
		for (auto& c : book)
		{
			c->xpos = transfrom->position.x+32 + (c->Rad)*cos(speed * (Game::clock)-c->first_phi);
			c->ypos = transfrom->position.y+32 + (c->Rad)*sin(speed * (Game::clock)-c->first_phi);
			c->update();
			c->draw();
			
		}
	};

	void upgrade()
	{
		if(amount < 3)
		{
			amount++;
		}
		if (exist < cooldown)
		{
			cooldown--;
			exist++;
		}
	}
	
};