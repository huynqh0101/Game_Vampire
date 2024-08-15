#pragma once
#include"Components.h"
#include"Game.h"
#include"TextureManager.h"

class Coin :public Component
{
private:
	int coin;
	int price;
	SDL_Texture* tex;
	SDL_Texture* tex2;
	std::string tmp;
	SDL_Rect dest,Coin_des;
public:
	
	Coin()
	{

		coin = 0;
		price = 0;
		
	}
	~Coin()
	{
		SDL_DestroyTexture(tex);

	}
	void init() override
	{
		tex2 = texturemanager::LoadTexture("UI/coin_bag.png");
		Coin_des = { 950,50,32,32 };
	};
	void update() override
	{
		int cnt = 0;
		if (coin < 10) cnt = 1;
		else
		{
			int a = coin;
			while (a > 0)
			{
				a /= 10;
				cnt++;
			}
		}
		dest = { 1000,50,20*cnt,20 };
		tmp = std::to_string(coin);
		SDL_Color color = { 255,255,255 };
		tex = texturemanager::LoadTextureFromFont("fonts/KO.ttf",color, tmp.c_str());
	};
	void draw() override
	{
		texturemanager::write(tex, dest);
		SDL_RenderCopy(Game::renderer, tex2, NULL, &Coin_des);
	};
	void colect_Coin()
	{
		coin+=1;
	}
	int getCoin()
	{
		return coin;
	}
	void purchase()
	{
		coin-= price;
	}
	void getPrice(int a)
	{
		price = a;
	}
	void setCoin(int coin)
	{
		this->coin = coin;
	}

};