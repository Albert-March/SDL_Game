#pragma once
#include "SDL.h"

#include <map>
#include <string>
#include <cassert>

#define RM RenderManager::GetInstance()

class RenderManager
{
public:
	static RenderManager* GetInstance()
	{
		static RenderManager instance;

		return &instance;
	}

	void Init();
	void Release();
	void ClearScreen();
	void RenderScreen();

	SDL_Renderer* GetRenderer() { return renderer; }

	void LoadTexture(std::string path);
	SDL_Texture* GetTexture(std::string path);

private:
	RenderManager() = default;
	RenderManager(RenderManager&) = default;
	RenderManager& operator= (const RenderManager&) = delete;
	~RenderManager();

	SDL_Window* window;
	SDL_Renderer* renderer;

	std::map<std::string, SDL_Texture*> textures;

	void InitSDL();
	void CreateWindowAndRenderer();
};