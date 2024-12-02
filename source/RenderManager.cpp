#include "RenderManager.h"
#include "SDL_image.h"

#include <iostream>

void RenderManager::Init()
{
	try
	{
		InitSDL();
		CreateWindowAndRenderer();
	}
	catch (std::exception& exception)
	{
		std::cout << exception.what();
		SDL_Quit();
		return;
	}
}

void RenderManager::Release()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void RenderManager::ClearScreen()
{
	SDL_RenderClear(renderer);
}

void RenderManager::RenderScreen()
{
	SDL_RenderPresent(renderer);
}

void RenderManager::LoadTexture(std::string path)
{
	SDL_Surface* surf = IMG_Load(path.c_str());
	assert(surf);

	textures[path] = SDL_CreateTextureFromSurface(renderer, surf);
	assert(textures[path]);

	SDL_FreeSurface(surf);
}

SDL_Texture* RenderManager::GetTexture(std::string path)
{
	if (textures.find(path) != textures.end())
		return textures[path];
	else
		return nullptr;
}

RenderManager::~RenderManager()
{
	for (std::map<std::string, SDL_Texture*>::iterator it = textures.begin(); it != textures.end(); it++)
		SDL_DestroyTexture(it->second);
}

void RenderManager::InitSDL()
{
	int result = SDL_Init(SDL_INIT_VIDEO);

	bool succes = result >= 0;
	if (!succes)
		throw SDL_GetError();
}

void RenderManager::CreateWindowAndRenderer()
{
	int result = SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE, &window, &renderer);

	bool succes = result >= 0;
	if (!succes)
		throw SDL_GetError();

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}
