#include"TextureManager.h"

 SDL_Texture* texturemanager::LoadTexture( const char* path) {
	SDL_Surface* tmp = IMG_Load(path);
	
	if (tmp == NULL) std::cout << "error";
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tmp);
	SDL_FreeSurface(tmp);
	return tex;
}
 SDL_Texture* texturemanager::LoadTextureFromFont(const char* path,SDL_Color color,std::string content)
 {
	
	 TTF_Font* font = TTF_OpenFont(path, 28);
	 if (font == NULL) 
	 {
		 std::cout << "not found";
	 }
	 SDL_Surface* fontsurface = TTF_RenderText_Solid(font, content.c_str(), color);	
	 SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, fontsurface);
	 SDL_FreeSurface(fontsurface);
	 TTF_CloseFont(font);
	 return tex;
 }

 void texturemanager::draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest,SDL_RendererFlip spriteflip)
 {
	 SDL_RenderCopyEx(Game::renderer, tex, &src, &dest, NULL, NULL, spriteflip);
 }
 void texturemanager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest)
 {
	 SDL_RenderCopy(Game::renderer, tex, &src, &dest);
 }
 void texturemanager::write(SDL_Texture* tex, SDL_Rect dest)
 {
	 SDL_RenderCopy(Game::renderer, tex, NULL, &dest);
 }
