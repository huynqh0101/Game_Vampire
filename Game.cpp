#include"Game.h"
#include"TextureManager.h"
#include"Map.h"
#include<ctime>
#include"Components.h"
#include"Collision.h"
#include"ECS.h"
#include<map>


std::map<std::string, int> mp;
std::map<int, std::string> Store_Of_Game;
std::string path;
int i = 0;
int j = 1;
std::map<int, std::string> upgrade_item;
int tmp_Store;
SDL_Renderer* Game::renderer = nullptr;
Map* map;
Manager manager;
Manager itemManager;
auto& player(manager.addEntity());
Manager EnemyManager;
int tmpspeed;
SDL_Event Game::event;
bool Game::isRunning;
int Game::timer;
int Game::clock;
int  Money;
bool upgrade_sound = 0;
bool start_music = 0;
bool Die = 0;
Mix_Chunk* Up_lv = NULL;
Mix_Music* bg_music = NULL;
Mix_Chunk* hit = NULL;
Mix_Chunk* die = NULL;
Mix_Chunk* pick_up = NULL;
Mix_Chunk* confirm = NULL;

Game::Game()
{};


Game::~Game()
{};


int count(int a)
{
	if (a < 10) return 1;
	int cnt = 0;
	while (a > 0)
	{
		a /= 10;
		cnt++;
	}
	
	return cnt;
}

void Game::init(const char *title, int xpos, int ypos, int width, int height, int fullscreen)
{
	type = Start;
	int flags = 0;
	if (fullscreen == 1) {
		flags = SDL_WINDOW_SHOWN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0 && TTF_Init() == 0) {
		std::cout << "Subsystem initialised!" << std::endl;
		gWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (gWindow) {
			std::cout << "Window created" << std::endl;
			renderer = SDL_CreateRenderer(gWindow, -1, 0);
		}
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "renderer created" << std::endl;
		}
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		}

		isRunning = 1;
		map = new Map("final_map.txt");
		
		player.addComponent<TransformComponent>(500,300);
		player.addComponent<SpriteComponent>("aniamtion-removebg-preview.png", 4, 150,1,32,32);
		player.addComponent<KeyBoardController>();
		player.addComponent<ColliderComponent>("player");
		player.addComponent<LifeOfPlayer>(100);
		player.addComponent<shot01>();
		player.addComponent<exp_Of_player>("exp.png");
		player.addComponent<Coin>();
		player.addComponent<Shot_02>();
		player.addComponent<Shot_03>();
		player.addComponent<Shadow>();
		srand(time(0));
		
		Store_Of_Game[0] = "store_photo/MaxHealth_inter.png";
		Store_Of_Game[1] = "store_photo/MoveSpeed_inter.png";
		Store_Of_Game[2] = "store_photo/Revival_inter.png";
		Store_Of_Game[3] = "store_photo/knife.png";
		Store_Of_Game[5] = "store_photo/Garlic.png";
		Store_Of_Game[4] = "store_photo/King_Bible.png";
		
		//initialize the information from the file
		std::fstream file("saved.txt");
		
		file >> Money;
		file >> player.getComponent<shot01>().ammount;
		file >> player.getComponent<Shot_02>().cooldown >> player.getComponent<Shot_02>().exist >> player.getComponent<Shot_02>().amount;
		file >> player.getComponent<TransformComponent>().speed;
		file >> player.getComponent<LifeOfPlayer>().hp;
		file >> player.getComponent<LifeOfPlayer>().life;
		file.close();


		upgrade_item[0] = "UI/weapon_upgrade/Empty_tome.png";
		upgrade_item[1] = "UI/weapon_upgrade/Bracer.png";
		upgrade_item[2] = "UI/weapon_upgrade/Duplicator.png";
		upgrade_item[3] = "UI/weapon_upgrade/Max_health.png";
		upgrade_item[4] = "UI/weapon_upgrade/Spinach.png";
		upgrade_item[5] = "UI/weapon_upgrade/Wings.png";
		upgrade_item[6] = "Reduce cooldown by 10%";
		upgrade_item[7] = "Increase the speed of projectiles";
		upgrade_item[8] = "Increase the amount of projectiles by 1";
		upgrade_item[9] = "Increase max health of Player by 30%";
		upgrade_item[10] = "Increase the damage by 10%";
		upgrade_item[11] = "Increase the speed of Player by 20%";


		read = 0;
		
		
		Up_lv = Mix_LoadWAV("sound/lvup.ogg");
		bg_music = Mix_LoadMUS("sound/VS_Music_v04-01.ogg");
		hit = Mix_LoadWAV("sound/VS_EnemyHit_v06-02.ogg");
		die = Mix_LoadWAV("sound/VS_GameOver_v02-01.ogg");
		pick_up = Mix_LoadWAV("sound/sfx_coin_double4.ogg");
		confirm = Mix_LoadWAV("sound/sfx_sounds_pause7_out.ogg");
	}
	else {
		isRunning = 0;
	}
	
	
}

void Game::update()
{
	manager.refresh();
	manager.update();
	itemManager.refresh();
	itemManager.update();
	EnemyManager.refresh();
	EnemyManager.update();


	//spawn the items in game
	if (clock/1000 % 100 == 0)
	{
		while(itemManager.entities.size()<6)
	{
		std::string f;
		if (itemManager.entities.size() % 3 == 0) f = "speed.png";
		else if (itemManager.entities.size() % 3 == 1) f = "strength.png";
		else f = "heart.png";
		int a = rand() % 1000;
		int b = rand() % 1000;
		auto& item(itemManager.addEntity());
		item.addComponent<TransformComponent>(a, b,32,32,1);
		item.addComponent<SpriteComponent>(f.c_str(), 16, 16);
		item.addComponent<ColliderComponent>(f.erase(f.find('.', 3)).c_str());
	}
	}

	//ckeck if level of player up
	if (player.getComponent<exp_Of_player>().lvup)
	{
		player.getComponent<TransformComponent>().velocity.x = player.getComponent<TransformComponent>().veloc_of_map.x = 0;
		player.getComponent<TransformComponent>().velocity.y = player.getComponent<TransformComponent>().veloc_of_map.y = 0;

		player.getComponent<exp_Of_player>().lvup = 0;
		
		type = Upgrade;

	}
	saved = 0;

	int speed = player.getComponent<TransformComponent>().speed;//save in oreder to easy to access

	// set the video map
	float tmp1 =  map->delta_x = -(player.getComponent<TransformComponent>().videomap.x - 500);
	float tmp2 = map->delta_y = -(player.getComponent<TransformComponent>().videomap.y - 300);
	
	//spawn the enemy
	int amonut_Of_Enemy = (clock / 2000) % 300;
	int hp_Of_Enemy = player.getComponent<exp_Of_player>().getlv() * 30+30 ;
	while(EnemyManager.entities.size()<amonut_Of_Enemy && ((clock / 1000) * 1000) %10000==0)
	{
		int a, b;
		a = rand() % 2000+500*pow(-1, EnemyManager.entities.size());
		b = rand() % 2000*pow(-1, EnemyManager.entities.size());
		auto& enemy(EnemyManager.addEntity());
		enemy.addComponent<TransformComponent>(a,b,128,102,1);
		if (EnemyManager.entities.size()%2==0)
		enemy.addComponent<SpriteComponent>("enemy_04.png",6,250,1,96,96);
		else 
			enemy.addComponent<SpriteComponent>("enemy_03.png", 6, 250, 1, 96, 96);
		enemy.addComponent<ColliderComponent>("enemy");
		enemy.addComponent<LifeOfEntiy>(hp_Of_Enemy);

		

	}
	//check the collision of bullet and enemy
	for (int i = 0; i < EnemyManager.entities.size(); i++)
	{
		int left = 0;
		int up = 1;
		int px = player.getComponent<TransformComponent>().position.x;
		int py = player.getComponent<TransformComponent>().position.y;
		int vx = player.getComponent<TransformComponent>().velocity.x;
		int vy = player.getComponent<TransformComponent>().velocity.y;
		if (EnemyManager.entities[i]->getComponent<TransformComponent>().position.x >= px)
		{
			left = 1;
			EnemyManager.entities[i]->getComponent<SpriteComponent>().spriteflip = SDL_FLIP_NONE;
		}
		else
		{
			EnemyManager.entities[i]->getComponent<SpriteComponent>().spriteflip = SDL_FLIP_HORIZONTAL;
		}
		float a = (-EnemyManager.entities[i]->getComponent<TransformComponent>().position.x + px);
		float b = (-EnemyManager.entities[i]->getComponent<TransformComponent>().position.y + py);
		float tmp = b / a;
		//check the method in transformation of enemies
		if (player.getComponent<TransformComponent>().veloc_of_map.x != 0)
		{
			//if velocity of map != 0
			EnemyManager.entities[i]->getComponent<TransformComponent>().position.Add(Vector2D(-player.getComponent<TransformComponent>().veloc_of_map.x * speed, b * 0.001));
		}
		if (player.getComponent<TransformComponent>().veloc_of_map.y != 0)
		{
			EnemyManager.entities[i]->getComponent<TransformComponent>().position.Add(Vector2D(a * 0.001, -player.getComponent<TransformComponent>().veloc_of_map.y * speed));
		}
		if (!Collision::AABB(player.getComponent<ColliderComponent>().rec, EnemyManager.entities[i]->getComponent<ColliderComponent>().rec) && abs(int(a)) > 30 && abs(int(b)) > 10)
			EnemyManager.entities[i]->getComponent<TransformComponent>().position.Add(Vector2D(pow(-1, left) * 2, pow(-1, left) * tmp * 2));
		else
		{
			EnemyManager.entities[i]->getComponent<TransformComponent>().position.Add(Vector2D(a * 0.01, b * 0.01));
		}
		//knife attacking
		for (int j = 0; j < player.getComponent<shot01>().projectiles.size(); j++)
			if (Collision::AABB(player.getComponent<shot01>().projectiles[j]->des, EnemyManager.entities[i]->getComponent<ColliderComponent>().rec))
			{

				EnemyManager.entities[i]->getComponent<TransformComponent>().position.Add(Vector2D(100 * (left == 1 ? 1 : -1), 0)); //push back the enemies
				player.getComponent<shot01>().projectiles[j]->coll = 1;//check the collision of bullet
				/*EnemyManager.entities[i]->getComponent<SpriteComponent>().animated = 1;*/
				EnemyManager.entities[i]->getComponent<LifeOfEntiy>().hp -= player.getComponent<shot01>().damage;
				EnemyManager.entities[i]->getComponent<SpriteComponent>().srcRect.x = 96 * 6;


			}

		//Book attacking
		{
			for (int j = 0; j < player.getComponent<Shot_02>().book.size(); j++)
			{
				if (Collision::AABB(player.getComponent<Shot_02>().book[j]->des, EnemyManager.entities[i]->getComponent<ColliderComponent>().rec))
				{
					EnemyManager.entities[i]->getComponent<SpriteComponent>().srcRect.x = 96 * 6;

					EnemyManager.entities[i]->getComponent<TransformComponent>().position.Add(Vector2D(30 * cos(player.getComponent<Shot_02>().speed * (Game::clock)) * (left == 1 ? 1 : -1), (EnemyManager.entities[i]->getComponent<TransformComponent>().position.y > player.getComponent<TransformComponent>().position.y) ? 30 : -30));
					EnemyManager.entities[i]->getComponent<LifeOfEntiy>().hp -= player.getComponent<Shot_02>().damage;
				}
			}
		}
		//garlic defense
		{
			int check_inRange = sqrt(pow((EnemyManager.entities[i]->getComponent<TransformComponent>().position.x + 64 - player.getComponent<Shot_03>().xCenter()), 2)
				+ pow((EnemyManager.entities[i]->getComponent<TransformComponent>().position.y + 64 - player.getComponent<Shot_03>().yCenter()), 2));
			if (check_inRange <= player.getComponent<Shot_03>().getRange() && player.getComponent<Shot_03>().cooldown())
			{
				EnemyManager.entities[i]->getComponent<LifeOfEntiy>().hp-= player.getComponent<Shot_03>().damage;
				EnemyManager.entities[i]->getComponent<SpriteComponent>().srcRect.x = 96 * 6;
			}
		}
		if (EnemyManager.entities[i]->getComponent<LifeOfEntiy>().hp <= 0)
		{
			if (rand() % 4 == 0)
			{
				auto& coin(itemManager.addEntity());
				coin.addComponent<TransformComponent>(EnemyManager.entities[i]->getComponent<TransformComponent>().position.x, EnemyManager.entities[i]->getComponent<TransformComponent>().position.y, 16, 16, 1);
				coin.addComponent<SpriteComponent>("coin.png", 32, 32);
				coin.addComponent<ColliderComponent>("coin");

			}
			else
				//throw the exp
			{
				auto& ex(itemManager.addEntity());
				ex.addComponent<TransformComponent>(EnemyManager.entities[i]->getComponent<TransformComponent>().position.x, EnemyManager.entities[i]->getComponent<TransformComponent>().position.y, 16, 16, 1);
				ex.addComponent<SpriteComponent>("exp_item.png", 32, 32);
				ex.addComponent<ColliderComponent>("exp");
			}


			EnemyManager.entities[i]->destroy();
		}
	}
	
	//pick up items and exp
	for (int i = 0; i < itemManager.entities.size(); i++)
	{
		itemManager.entities[i]->getComponent<TransformComponent>().position.Add(Vector2D(-speed* player.getComponent<TransformComponent>().veloc_of_map.x, -speed* player.getComponent<TransformComponent>().veloc_of_map.y));
		int a = -itemManager.entities[i]->getComponent<TransformComponent>().position.x + player.getComponent<TransformComponent>().position.x;
		int b = -itemManager.entities[i]->getComponent<TransformComponent>().position.y + player.getComponent<TransformComponent>().position.y;
		//get the distance between player and item 
		if (sqrt(a * a + b * b)<150) itemManager.entities[i]->getComponent<TransformComponent>().isInRange = 1;
		if (itemManager.entities[i]->getComponent<TransformComponent>().isInRange)
		{
			itemManager.entities[i]->getComponent<TransformComponent>().position.Add(Vector2D(0.3*a, b*0.3));
			if (Collision::AABB(itemManager.entities[i]->getComponent<ColliderComponent>().rec, player.getComponent<ColliderComponent>().rec))
			{
				Mix_PlayChannel(-1, pick_up, 0);
				std::string tmp = itemManager.entities[i]->getComponent<ColliderComponent>().tag; //get the name of item
				mp[tmp] = (clock / 1000) * 1000;//start the time of the affect of item

				if (tmp == "speed")
					player.getComponent<TransformComponent>().speed *= 1.5; //item lightning

				else if (tmp == "strength")//item increase the spped of gun
				{
					player.getComponent<shot01>().reload = 500;
					player.getComponent<shot01>().i = (clock) / 500 + 1;
				}
				else if (tmp == "heart")//item increase the spped of gun
				{
					int a = player.getComponent<LifeOfPlayer>().maxhp - player.getComponent<LifeOfPlayer>().hp;
					player.getComponent<LifeOfPlayer>().hp += (a>30)?30:a;
				}
				else if (tmp == "exp")
				{
					player.getComponent<exp_Of_player>().up();
					
				}
				else if (tmp == "coin")
				{
					player.getComponent<Coin>().colect_Coin();
				}
				itemManager.entities[i]->destroy();
				
			}
		}
	
	}
	//check time of item
	for (auto c : mp)
	{
		
		if (clock - c.second >= 5000)//check the using time of items
		{
			
			std::string tmp = c.first;
			if (tmp == "speed")
			{
				
				player.getComponent<TransformComponent>().speed /= 1.5;
				mp[tmp] = 100000000;
				
			}
			else if (tmp == "strength")
			{
				player.getComponent<shot01>().reload = 1500;
				player.getComponent<shot01>().i = (clock) / 1500+1;
				
			}
		}
	}
	int power_Of_Enemy = player.getComponent<exp_Of_player>().getlv()*2;
	int check = 0;
	
	for (int i = 0; i < EnemyManager.entities.size(); i++)
	{
		
		if (Collision::AABB(player.getComponent<ColliderComponent>().rec, EnemyManager.entities[i]->getComponent<ColliderComponent>().rec))
		{
			Mix_PlayChannel(-1, hit, 0);
			player.getComponent<LifeOfPlayer>().loss_HP = 1;
			check = clock;
			player.getComponent<LifeOfPlayer>().hp -= power_Of_Enemy;
			
		}
		if (clock - check > 50)
		{
			player.getComponent<LifeOfPlayer>().loss_HP = 0;
		}
	}
	
	
	if (player.getComponent<LifeOfPlayer>().hp <= 0)
	{
		
		player.getComponent<LifeOfPlayer>().life--;
		player.getComponent<LifeOfPlayer>().hp = 100;
		type = Lose;
		
	}
};

void Game::Game_start()
{
	if (start_music == 0)
	{
		Mix_PlayMusic(bg_music, -1);
		start_music = 1;
	}
	std::fstream file("saved.txt");

	file >> Money;
	file >> player.getComponent<shot01>().ammount;
	file >> player.getComponent<Shot_02>().cooldown >> player.getComponent<Shot_02>().exist >> player.getComponent<Shot_02>().amount;
	file >> player.getComponent<TransformComponent>().speed;
	file >> player.getComponent<LifeOfPlayer>().hp;
	file >> player.getComponent<LifeOfPlayer>().life;
	file.close();
	player.getComponent<exp_Of_player>().lv = 1;
	player.getComponent<LifeOfPlayer>().maxhp = player.getComponent<LifeOfPlayer>().hp;
	player.getComponent<exp_Of_player>().maxExp = 100;
	player.getComponent<exp_Of_player>().exp = 0;
	Money += player.getComponent<Coin>().getCoin();
	player.getComponent<Coin>().setCoin(0);
	clock = 0;
	player.getComponent<shot01>().i = 1;
	for (int i = 0; i < EnemyManager.entities.size(); i++)
	{
		EnemyManager.entities[i]->destroy();
	}
	for (int i = 0; i < itemManager.entities.size(); i++)
	{
		itemManager.entities[i]->destroy();
	}
	
	player.getComponent<TransformComponent>().velocity.x = 0;
	player.getComponent<TransformComponent>().velocity.y = 0;
	player.getComponent<TransformComponent>().veloc_of_map.x = 0;
	player.getComponent<TransformComponent>().veloc_of_map.y = 0;
	SDL_Color color = { 255,255,255 };
	SDL_Rect start, quit, option, powerup;
	SDL_Rect Left_arrow;
	SDL_Rect Right_arrow;
	SDL_Rect Start_des, Quit_des, Powerup_rec;
	Start_des = { 560,560,150,40 };
	Powerup_rec = { 530,660,200,50 };
	Quit_des = { 115,37,120,35 };
	SDL_Rect Coin_rec = { 600,27,20*count(Money),30};
	SDL_Texture* tex_Start = texturemanager::LoadTextureFromFont("fonts/KO.ttf",color, "START");
	SDL_Texture* tex_Quit = texturemanager::LoadTextureFromFont("fonts/KO.ttf",color, "QUIT");
	SDL_Texture* tex_Powerup = texturemanager::LoadTextureFromFont("fonts/KO.ttf",color, "POWER UP");
	SDL_Texture* tex_Coin = texturemanager::LoadTextureFromFont("fonts/KO.ttf",color, std::to_string(Money));
	start.x = 530;
	start.y = 550;
	start.w = 200;
	start.h = 60;

	powerup.x = 500;
	powerup.y = 650;
	powerup.w = 260;
	powerup.h = 85;

	quit.x = 100;
	quit.y = 30;
	quit.w = 150;
	quit.h = 55;
	std::map<int, std::string> mp;
	
	mp[0] = "UI/arrow_01.png";
	mp[1] = "UI/arrow_02.png";
	mp[2] = "UI/arrow_03.png";
	mp[3] = "UI/arrow_04.png";
	mp[4] = "UI/arrow_05.png";

	mp[5] = "UI/button3_a.png";
	mp[6] = "UI/button2_a.png";
	mp[7] = "UI/button1_a.png";

	int i = rtime / 200 % 5;
	if (j%3 == 1)
	{
		Left_arrow = { 485,550,64,64 };
		Right_arrow = { 710,550,64,64 };
	}
	else if (j % 3== 0)
	{
		Left_arrow = { 50,30,64,64 };
		Right_arrow = { 237,30,64,64 };
	}
	else if (j % 3 == 2)
	{
		Left_arrow = { 550-95,650+18,64,64 };
		Right_arrow = { 710+35,650+18,64,64 };
	}

	SDL_Texture* Background = texturemanager::LoadTexture("UI/Start_background.png");
	SDL_Texture* Quit = texturemanager::LoadTexture(mp[5].c_str());
	SDL_Texture* Option = texturemanager::LoadTexture(mp[6].c_str());
	SDL_Texture* Powerup = texturemanager::LoadTexture(mp[7].c_str());
	SDL_Texture* left_arrow = texturemanager::LoadTexture(mp[i].c_str());

	SDL_RenderCopy(renderer, Background, NULL, NULL);
	SDL_RenderCopy(renderer, Option, NULL, &start);
	SDL_RenderCopy(renderer, Powerup, NULL, &powerup);
	SDL_RenderCopy(renderer, Quit, NULL, &quit);
	SDL_RenderCopy(renderer, left_arrow, NULL, &Left_arrow);
	SDL_RenderCopyEx(renderer, left_arrow, NULL, &Right_arrow, NULL, NULL, SDL_FLIP_HORIZONTAL);
	texturemanager::write(tex_Start, Start_des);
	texturemanager::write(tex_Quit, Quit_des);
	texturemanager::write(tex_Powerup, Powerup_rec);
	texturemanager::write(tex_Coin, Coin_rec);
	SDL_RenderPresent(Game::renderer);
	SDL_DestroyTexture(Background);
	SDL_DestroyTexture(Quit);
	SDL_DestroyTexture(Option);
	SDL_DestroyTexture(Powerup);
	SDL_DestroyTexture(left_arrow);
	SDL_DestroyTexture(tex_Start);
	SDL_DestroyTexture(tex_Quit);
	SDL_DestroyTexture(tex_Powerup);
	SDL_DestroyTexture(tex_Coin);

	if (event.type == SDL_KEYUP)
	{
		
		switch (event.key.keysym.sym)
		{
		case SDLK_LEFT:
			j--;
			break;
		case SDLK_RIGHT:
			j++;
			break;
		case SDLK_j:
			start_music = 0;
			Mix_HaltMusic();
			if (j % 3 == 1)
			{
				type = Running;
			}
			else if (j % 3 == 0)
			{
				isRunning = 0;
			}
			else
			{
				type = Store;
			}
			break;
		}
	}
}

void Game:: upgrade()
{
	player.getComponent<TransformComponent>().velocity.x = 0;
	player.getComponent<TransformComponent>().velocity.y = 0;
	player.getComponent<TransformComponent>().veloc_of_map.x = 0;
	player.getComponent<TransformComponent>().veloc_of_map.y = 0;
	if (upgrade_sound == 0)
	{
		Mix_PlayChannel(-1, Up_lv, 0);
		upgrade_sound = 1;
	}
	SDL_Color color1 = { 56,255,100 };
	SDL_Color color2 = { 56,255,100 };
	SDL_Color color3 = { 56,255,100 };
	int x, y;
	Uint32 mousestate = SDL_GetMouseState(&x, &y);
	int i = clock % 6;
	SDL_Texture* item1 = texturemanager::LoadTexture(upgrade_item[(i) % 6].c_str());
	SDL_Texture* item2 = texturemanager::LoadTexture(upgrade_item[(i+1) % 6].c_str());
	SDL_Texture* item3 = texturemanager::LoadTexture(upgrade_item[(i+2) % 6].c_str());

	
	SDL_Rect i1,t1,t2,t3, i2, i3;
	i1 = {380,200,64,64};
	i2 = {380,400,64,64 };
	i3 = { 380,600,64,64 };
	t1 = { 480,210,350,30 };
	t2 = { 480,410,350,30 };
	t3 = { 480,610,350,30 };

	map->DrawMap();
	SDL_Rect des;
	des = { 300,50,600,700 };

	if (x > 380 && x <= 444 && y>=200&& y<=264)
	{
		i1 = { 380-16,200-16,106,106 };
		color1 = { 56,255,100 };
		if (event.type == SDL_MOUSEBUTTONUP && event.button.clicks == 1)
		{
			Mix_PlayChannel(-1, confirm, 0);
			upgrade_sound = 0;
			switch (i%6)
			{
			case 0:
				player.getComponent<shot01>().reload -= player.getComponent<shot01>().reload * 0.1;
				player.getComponent<Shot_02>().cooldown -= player.getComponent<Shot_02>().cooldown * 0.1;
				player.getComponent<Shot_03>().coolTime -= player.getComponent<Shot_03>().coolTime * 0.1;
				break;
			case 1:
				player.getComponent<shot01>().veloc += player.getComponent<shot01>().veloc * 0.1;
				player.getComponent<Shot_02>().speed += player.getComponent<Shot_02>().speed* 0.1;
				break;
			case 2:

				player.getComponent<shot01>().ammount += 1;
				player.getComponent<Shot_02>().amount += 1;

				break;
			case 3:
				player.getComponent<LifeOfPlayer>().maxhp *= 1.3;
				player.getComponent<LifeOfPlayer>().hp = player.getComponent<LifeOfPlayer>().maxhp;
				break;
			case 4:
				player.getComponent<shot01>().damage += player.getComponent<shot01>().damage * 0.1;
				player.getComponent<Shot_02>().damage += player.getComponent<Shot_02>().damage * 0.1;
				player.getComponent<Shot_03>().damage += player.getComponent<Shot_03>().damage * 0.1;
				break;
			case 5:
				player.getComponent<TransformComponent>().speed += player.getComponent<TransformComponent>().speed * 0.1;
				break;

			}
			type = Running;
		}
	}
	else 
	{
		i1 = { 380,200,64,64 };
		color1 = { 56,160,100 };
	}
	if (x > 380 && x <= 444 && y >= 400 && y <= 464)
	{
		i2 = { 380 - 16,400 - 16,106,106 };
		color2 = { 56,255,100 };

		if (event.type == SDL_MOUSEBUTTONUP&&event.button.clicks == 1)
		{
			Mix_PlayChannel(-1, confirm, 0);
			upgrade_sound = 0;
			switch ((i+1)%6)
			{
			case 0:
				player.getComponent<shot01>().reload -= player.getComponent<shot01>().reload * 0.1;
				player.getComponent<Shot_02>().cooldown -= player.getComponent<Shot_02>().cooldown * 0.1;
				player.getComponent<Shot_03>().coolTime -= player.getComponent<Shot_03>().coolTime * 0.1;
				break;
			case 1:
				player.getComponent<shot01>().veloc += player.getComponent<shot01>().veloc * 0.1;
				player.getComponent<Shot_02>().speed += player.getComponent<Shot_02>().speed * 0.1;
				break;
			case 2:
				player.getComponent<shot01>().ammount += 1;
				player.getComponent<Shot_02>().amount += 1;
				break;
			case 3:
				player.getComponent<LifeOfPlayer>().maxhp *= 1.3;
				player.getComponent<LifeOfPlayer>().hp = player.getComponent<LifeOfPlayer>().maxhp;
				break;
			case 4:
				player.getComponent<shot01>().damage += player.getComponent<shot01>().damage * 0.1;
				player.getComponent<Shot_02>().damage += player.getComponent<Shot_02>().damage * 0.1;
				player.getComponent<Shot_03>().damage += player.getComponent<Shot_03>().damage * 0.1;
				break;
			case 5:
				player.getComponent<TransformComponent>().speed += player.getComponent<TransformComponent>().speed * 0.1;
				break;

			}
			type = Running;
		}
	}
	else
	{
		i2 = { 380,400,64,64 };
		color2 = { 56,160,100 };
	}
	if (x > 380 && x <= 444 && y >= 600 && y <= 664)
	{
		i3 = { 380 - 16,600- 16,106,106 };
		color3 = { 56,255,100 };
		if (event.type == SDL_MOUSEBUTTONUP && event.button.clicks == 1)
		{
			Mix_PlayChannel(-1, confirm, 0);
			upgrade_sound = 0;
			switch ((i+2)%6)
			{
			case 0:
				player.getComponent<shot01>().reload -= player.getComponent<shot01>().reload * 0.1;
				player.getComponent<Shot_02>().cooldown -= player.getComponent<Shot_02>().cooldown * 0.1;
				player.getComponent<Shot_03>().coolTime -= player.getComponent<Shot_03>().coolTime * 0.1;
				break;
			case 1:
				player.getComponent<shot01>().veloc += player.getComponent<shot01>().veloc * 0.1;
				player.getComponent<Shot_02>().speed += player.getComponent<Shot_02>().speed * 0.1;
				break;
			case 2:
				if(player.getComponent<shot01>().ammount<=3)
				player.getComponent<shot01>().ammount += 1;
				if(player.getComponent<Shot_02>().amount<=3)
				player.getComponent<Shot_02>().amount += 1;
				break;
			case 3:
				player.getComponent<LifeOfPlayer>().maxhp *= 1.3;
				player.getComponent<LifeOfPlayer>().hp = player.getComponent<LifeOfPlayer>().maxhp;
				break;
			case 4:
				player.getComponent<shot01>().damage += player.getComponent<shot01>().damage * 0.1;
				player.getComponent<Shot_02>().damage += player.getComponent<Shot_02>().damage * 0.1;
				player.getComponent<Shot_03>().damage += player.getComponent<Shot_03>().damage * 0.1;
				break;
			case 5:
				player.getComponent<TransformComponent>().speed += player.getComponent<TransformComponent>().speed * 0.1;
				break;

			}
			type = Running;

		}
	}
	else
	{
		i3 = { 380,600,64,64 };
		color3 = { 56,160,100 };
	}

	SDL_Texture* tex1 = texturemanager::LoadTextureFromFont("fonts/KO.ttf", color1, upgrade_item[(i %6)+6]);
	SDL_Texture* tex2 = texturemanager::LoadTextureFromFont("fonts/KO.ttf", color2, upgrade_item[((i+1) %6)+6]);
	SDL_Texture* tex3 = texturemanager::LoadTextureFromFont("fonts/KO.ttf", color3, upgrade_item[((i + 2)%6)+6]);
	SDL_Texture* tex = texturemanager::LoadTexture("UI/Card X3.png");
	SDL_RenderCopy(renderer, tex, NULL, &des);
	SDL_RenderCopy(renderer, item1, NULL, &i1);
	SDL_RenderCopy(renderer, item2, NULL, &i2);
	SDL_RenderCopy(renderer, item3, NULL, &i3);
	SDL_RenderCopy(renderer, tex1, NULL, &t1);
	SDL_RenderCopy(renderer, tex2, NULL, &t2);
	SDL_RenderCopy(renderer, tex3, NULL, &t3);




	SDL_RenderPresent(renderer);
	SDL_DestroyTexture(tex);
	SDL_DestroyTexture(item1);
	SDL_DestroyTexture(item3);
	SDL_DestroyTexture(item2);
	SDL_DestroyTexture(tex1);
	SDL_DestroyTexture(tex2);
	SDL_DestroyTexture(tex3);

}
void Game::store()
{

	player.getComponent<Coin>().setCoin(Money);
	SDL_Color col_card = { rtime % 255,255,rtime % 255 };
	SDL_Texture* card= texturemanager::LoadTexture("UI/Card X5.png");
	SDL_Rect Card,tCard;
	SDL_Texture* textCard = texturemanager::LoadTextureFromFont("fonts/KO.ttf", col_card, "Not enough Money");
	SDL_Texture* coin = texturemanager::LoadTextureFromFont("fonts/KO.ttf", col_card,"Coin: " + std::to_string(player.getComponent<Coin>().getCoin()));
	SDL_Rect money = { 575,500,100,30 };
	int x, y;
	Uint32 mousestate = SDL_GetMouseState(&x, &y);
	SDL_Texture* tex = texturemanager::LoadTexture("store_photo/storeRage.png");
	SDL_RenderCopy(renderer, tex, NULL, NULL);
	SDL_Texture* tex2 = texturemanager::LoadTexture("store_photo/22.png");
	SDL_Rect des2; des2.x = 1100; des2.y = 100;
	if (x >= 1100 && x <= 1142 && y > 107 && y <= 140)
	{
		des2.w = des2.h = 70;
	}
	else des2.w = des2.h = 45;
	SDL_RenderCopy(renderer, tex2, NULL, &des2);

	

	switch (event.type)
	{
	case SDL_KEYUP:
	{
		
		if (event.key.keysym.sym == SDLK_LEFT)
		{
			if (i == 0)
			{
				i = 5;
			}
			else i--;

		}
		else if (event.key.keysym.sym == SDLK_RIGHT)
		{
			i++;
		}
		else if (event.key.keysym.sym == SDLK_j)
		{
			
			saved = 0;
			switch (i%6)
			{
			case 0:
			{
				if (player.getComponent<Coin>().getCoin() > 50)
				{
					Mix_PlayChannel(-1, confirm, 0);
					Card = { 200,200,0,0 };
					player.getComponent<LifeOfPlayer>().maxhp *= 1.3;
					player.getComponent<Coin>().getPrice(50);
					player.getComponent<Coin>().purchase();
				}
				else
				{
					tmp_Store = SDL_GetTicks();

				}
				
				break;
			}
			case 1:
			{
				if (player.getComponent<Coin>().getCoin() > 75)
				{
					Mix_PlayChannel(-1, confirm, 0);
					Card = { 200,200,0,0 };
					player.getComponent<TransformComponent>().speed *= 1.3;
					player.getComponent<Coin>().getPrice(50);
					player.getComponent<Coin>().purchase();
				}
				else tmp_Store = SDL_GetTicks();
				
				break;
			}
			case 2:
			{
				if (player.getComponent<Coin>().getCoin() > 500)
				{
					Mix_PlayChannel(-1, confirm, 0);
					Card = { 200,200,0,0 };
					player.getComponent<LifeOfPlayer>().life++;
					player.getComponent<Coin>().getPrice(500);
					player.getComponent<Coin>().purchase();
				}
				else tmp_Store = SDL_GetTicks();

				break;
			}
			case 3:
			{
				Mix_PlayChannel(-1, confirm, 0);
				if (player.getComponent<Coin>().getCoin() > 500)
				{
					Card = { 200,200,0,0 };
					if (player.getComponent<shot01>().ammount < 4)
					{
						player.getComponent<shot01>().ammount++;
					}
					else if (player.getComponent<shot01>().reload >= 500)
					{
						player.getComponent<shot01>().reload -= 100;
					}
					else
					{

						player.getComponent<shot01>().veloc += 10;
					}
					player.getComponent<Coin>().getPrice(500);
					player.getComponent<Coin>().purchase();
				}
				else tmp_Store = SDL_GetTicks();

				break;
			}
			case 4:
			{
				Mix_PlayChannel(-1, confirm, 0);
				if (player.getComponent<Coin>().getCoin() > 500)
				{
					Card = { 200,200,200,0 };
					if (!player.hasComponent<Shot_02>())
					{
						player.addComponent<Shot_02>();
					}
					else
					player.getComponent<Shot_02>().upgrade();
					player.getComponent<Coin>().getPrice(500);
					player.getComponent<Coin>().purchase();
				}
				else tmp_Store = SDL_GetTicks();

				break;
			}
			case 5:
			{
				Mix_PlayChannel(-1, confirm, 0);
				if (player.getComponent<Coin>().getCoin() > 500)
				{
					Card = { 200,200,200,0};
					player.getComponent<Shot_03>().upgrade();
					player.getComponent<Coin>().getPrice(500);
					player.getComponent<Coin>().purchase();
					std::cout << "purchased" << " ";
					std::cout << player.getComponent<Shot_03>().getRange();
				}
				else tmp_Store = SDL_GetTicks();

				break;
			}
			}
		}
		break;
	}
	case SDL_MOUSEBUTTONUP:
	{
		if (event.button.clicks == 1 && event.button.x >= 1100 && event.button.x <= 1142 && event.button.y >= 107 && event.button.y <=140)
		{
			type = Start;

		}
		
		break;
	}
	}

	if (rtime - tmp_Store > 1500)
	{
		tCard = { 0,0,0,0 };
		Card = { 200,200,0,0 };
	}
	else
	{
		tCard = { 524,420,150,30 };
		Card = { 500,400,200,100 };
	}
	 
		SDL_Rect des = { 0,620,1280,180 };
		SDL_Texture* tex1 = texturemanager::LoadTexture(Store_Of_Game[int(i % 6)].c_str());
		SDL_RenderCopy(renderer, tex1, NULL, &des);
		SDL_RenderCopy(renderer, card, NULL, &Card);
		SDL_RenderCopy(renderer, textCard, NULL, &tCard);
		SDL_RenderCopy(renderer, coin, NULL, &money);
		SDL_RenderPresent(renderer);
		SDL_DestroyTexture(tex1);
		SDL_DestroyTexture(tex);
		SDL_DestroyTexture(tex2);
		SDL_DestroyTexture(textCard);
		SDL_DestroyTexture(card);
		SDL_DestroyTexture(coin);
		Money = player.getComponent<Coin>().getCoin();
		player.getComponent<Coin>().setCoin(0);
}
void Game::GameLose()
{
	SDL_Color color = { 255,255,255 };
	player.getComponent<TransformComponent>().velocity.x = 0;
	player.getComponent<TransformComponent>().velocity.y = 0;
	player.getComponent<TransformComponent>().veloc_of_map.x = 0;
	player.getComponent<TransformComponent>().veloc_of_map.y = 0;
	if (Die == 0)
	{
		Mix_PlayChannel(-1, die, 0);
		Die = 1;
	}
	
	std::map<int, std::string> mp;
	mp[0] = "UI/arrow_01.png";
	mp[1] = "UI/arrow_02.png";
	mp[2] = "UI/arrow_03.png";
	mp[3] = "UI/arrow_04.png";
	mp[4] = "UI/arrow_05.png";
	SDL_Rect Left_arrow;
	SDL_Rect Right_arrow;
	Left_arrow = { 480,480,64,64 };
	Right_arrow = { 705,480,64,64 };
	SDL_Texture* tex2 = texturemanager::LoadTexture("UI/Game_over.png");
	SDL_Texture* tex3;
	SDL_Texture* point = texturemanager::LoadTextureFromFont("fonts/KO.ttf", color, "Score: " + std::to_string(clock));
	SDL_Rect Point = { 570,550,count(clock)*20,30};

	SDL_RenderCopy(Game::renderer, tex2, NULL, NULL);
	SDL_Rect des = { 570,485,100,30 };
	if (player.getComponent<LifeOfPlayer>().life > 0)
	{
		tex3 = texturemanager::LoadTextureFromFont("fonts/KO.ttf", color, "Respawn");
	}
	else tex3 = texturemanager::LoadTextureFromFont("fonts/KO.ttf", color, "Quit");
	SDL_Texture* arrow = texturemanager::LoadTexture(mp[(rtime / 200) % 5].c_str());
	SDL_RenderCopyEx(renderer, arrow, NULL, &Left_arrow, NULL, NULL, SDL_FLIP_NONE);
	SDL_RenderCopyEx(renderer, arrow, NULL, &Right_arrow, NULL, NULL, SDL_FLIP_HORIZONTAL);
	SDL_RenderCopy(renderer, tex3, NULL, &des);
	if(player.getComponent<LifeOfPlayer>().life <= 0)
	SDL_RenderCopy(renderer, point, NULL, &Point);
	SDL_RenderPresent(Game::renderer);
	SDL_DestroyTexture(tex2);
	SDL_DestroyTexture(arrow);
	SDL_DestroyTexture(point);

	if (event.type == SDL_KEYUP)
	{
		
		if (event.key.keysym.sym == SDLK_j)
		{
			type = (player.getComponent<LifeOfPlayer>().life > 0) ? Running : Start;
			Die = 0;
			
			if (type == Start)
			{
				if (read == 0)
				{
					std::fstream file("saved.txt");
					int n;
					file >> n;
					file >> player.getComponent<shot01>().ammount;
					file >> player.getComponent<Shot_02>().cooldown >> player.getComponent<Shot_02>().exist >> player.getComponent<Shot_02>().amount;
					file >> player.getComponent<TransformComponent>().speed;
					file >> player.getComponent<LifeOfPlayer>().hp;
					file >> player.getComponent<LifeOfPlayer>().life;

					file.close();
					read = 1;
				}
				rtime = 0;
				clock = 0;
				player.getComponent<shot01>().i = 1;
				for (int i = 0; i < EnemyManager.entities.size(); i++)
				{
					EnemyManager.entities[i]->destroy();
				}
				player.getComponent<LifeOfPlayer>().loss_HP = 0;
			}
		}
	}
	


}

void Game::gameSaved()
{

	{
		std::fstream file_write("saved.txt");


		//


		file_write << Money << " ";
		//save the gold


		//
		file_write << player.getComponent<shot01>().ammount << " ";
		// saved the amount of knife


		//
		file_write << player.getComponent<Shot_02>().cooldown << " " << player.getComponent<Shot_02>().exist << " " << player.getComponent<Shot_02>().amount << " ";
		//saved the book

		//
		file_write << player.getComponent<TransformComponent>().speed << " ";
		//saved the speed;

		//
		file_write << player.getComponent<LifeOfPlayer>().hp << " ";
		//saved the hp

		//
		file_write << player.getComponent<LifeOfPlayer>().life;
		//saved the amount of life
		file_write.close();


	}
}

void Game::pause()
{
	SDL_RenderClear(renderer);
	map->DrawMap();

	itemManager.draw();
	EnemyManager.draw();
	manager.draw();

	SDL_RenderPresent(renderer);


}

void Game::setTime()
{
	if (type != Running)
	{
		rtime = SDL_GetTicks() - clock;
		std::cout << rtime << std::endl << "clock " << clock << std::endl;
	}
	else clock = SDL_GetTicks() - rtime;
}


void Game::HandleEvent() {

	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = 0;
		break;
	////case SDL_MOUSEBUTTONUP:
	////{
	////	
	////	read = 0;
	////	/*if (event.button.clicks == 1 && event.button.x >= 540 && event.button.x<=727 && event.button.y >= 541 && event.button.y<=610 && type == Start)
	////	{
	////		type = Running;

	////	}
	////	else if (event.button.clicks == 1 && event.button.x >= 556 && event.button.x <= 712 && event.button.y >= 704 && event.button.y <= 768 && type == Start)
	////	{
	////		type = Store;

	////	}*/


	////	break;
	//}
	case SDL_KEYUP:
	{
		if (event.key.keysym.sym == SDLK_ESCAPE&&type == Running)
		{
			type = Start;
		}
		
		else if (event.key.keysym.sym == SDLK_p&&type == Running)
		{
			type = Pause;
		}
		else if (event.key.keysym.sym == SDLK_p && type == Pause)
		{
			type = Running;
		}
	}
	default:
		break;
	}
}
void Game::render() {
	SDL_RenderClear(renderer);
	map->DrawMap();
	itemManager.draw();
	EnemyManager.draw();
	manager.draw();
	
	SDL_RenderPresent(renderer);
	
}

void Game::clean()
{
	SDL_DestroyWindow(gWindow);
	SDL_DestroyRenderer(renderer);
	Mix_FreeChunk(hit);
	Mix_FreeChunk(die);
	Mix_FreeChunk(pick_up);
	Mix_FreeChunk(confirm);
	Mix_FreeMusic(bg_music);

	Mix_Quit();
	TTF_Quit();

	SDL_Quit();
}


