#include "Game.h"
#include"TextureManager.h"

Game* game = NULL;
int main(int argc, char* argv[]) {
	game = new Game();
	game->init("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 800, 1);
	
	
	
	while (game->running())
	{
		game->setTime();
		
		if (game->type == Start)
		{
			game->Game_start();
			game->HandleEvent();
			game->gameSaved();
		}
		else if (game->type == Pause)
		{
			game->pause();
			game->HandleEvent();
		}
		else if (game->type == Store)
		{
			game->store();
			game->HandleEvent();
			game->gameSaved();
		}
		else if (game->type == Running)
		{
			game->HandleEvent();
			game->update();
			game->render();
			SDL_Delay(30);
		}
		else if (game->type == Upgrade)
		{
			game->upgrade();
			game->HandleEvent();
		}
		else if (game->type == Lose)
		{
			game->GameLose();
			game->HandleEvent();
			if(game->read == 1)
			game->gameSaved();
		}
	}
	
	

	
	
	game->clean();
	return 0;
}