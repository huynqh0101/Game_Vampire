
#ifndef Game_H
#define Game_H
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>
#include<iostream>
#include<fstream>

enum Gametype
{
	Start,
	Pause,
	Store,
	Running,
	Upgrade,
	Lose
};
class Game {
public:
	Gametype type = Start;
	Game();
	~Game();
	void init(const char* title, int xpos, int ypos, int width, int height, int fullscreen);
	void update();
	void HandleEvent();
	void render();
	void clean();
	bool running() 
	{
		return isRunning;
	}
	static SDL_Renderer* renderer;
	static SDL_Event event;
	static bool isRunning;
	static int timer;
	static int clock;
	void Game_start();
	void GameLose();
	void upgrade();
	void store();
	void pause();
	void setTime();
	void gameSaved();
	int saved = 0;
	int read = 0;

private:
	int rtime;
	
	SDL_Window* gWindow = NULL;
	


};


#endif 
