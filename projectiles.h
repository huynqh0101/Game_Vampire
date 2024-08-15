#pragma once
#include"Game.h"
#include"TextureManager.h"
#include<map>
//xây dựng 1 hàm để tạo ra đạn
//xây dụng thuọcc tính bắn đạn từ hàm tạo đạn trên
//thêm sự bắn đạn từ bàn phím.
class CreateProjectiles
{
public:
	int xpos;
	int ypos;
	int dir = 1;
	int scale;
	bool coll = 0;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	std::string path;
	SDL_Texture* tex;
	SDL_Texture* tex2;
	std::map<int,std::string> mp;
	SDL_Rect src, des, tail_des;
	CreateProjectiles(int srcW,int srcH,std::string mpath,int mscale) 
	{
		this->path = mpath;
		src.x = src.y = 0;
		src.w = srcW;
		src.h = srcH;
		this->scale = mscale;
	}
	

	
	void init()
	{
		mp[0] = "Shadow_Of_Knife_01.png";
		mp[1] = "Shadow_Of_Knife_02.png";
		des.w =50;
		des.h = 16;
		tail_des.w = 50;
		tail_des.h = 16;
	}
	
	void update()
	{
		if (dir == -1) this->flip = SDL_FLIP_HORIZONTAL;
		des.x = xpos+30;
		des.y = ypos+15;
		tail_des.x = des.x - 30*dir;
		tail_des.y = des.y;
	}
	void draw()
	{
		tex2 = texturemanager::LoadTexture(mp[int((Game::clock/150)%2)].c_str());
		tex = texturemanager::LoadTexture(path.c_str());
		texturemanager::draw(tex2, src, tail_des, flip);
		texturemanager::draw(tex, src, des, flip);
		SDL_DestroyTexture(tex);
	}
	
};