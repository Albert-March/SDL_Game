//#include <SDL.h>
//#include <SDL_image.h>
#include "Game.h"
#include <exception>
#include <iostream>
#include "InputManager.h"
#include "AABB.h"
#include "TimeManager.h"

int main(int argc, char* args[]) {

	Game game;
	
	try {
		game.Init();
	}
	catch (std::exception& exception)
	{
		std::cout << "Error: " << exception.what();
		game.Release();
		return-1;
	}

	bool playing = true;
	while (playing)
	{
		TIME.Update();
		std::cout << TIME.GetDeltaTime() << std::endl;
		if (TIME.ShouldUpdateGame())
		{
			playing = !Input.Listen();
			game.Update();
			game.Render();
			TIME.ResetDeltaTime();
		}
	}

	game.Release();

	return 0;






	//SDL_Window* _window = 0;
	//SDL_Renderer* _renderer = 0;

	////1) Initialize SDL
	//if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
	//{
	//	//2) Create pointer to our window
	//	_window = SDL_CreateWindow(
	//		"Hello world",          //Title
	//		SDL_WINDOWPOS_CENTERED, //x
	//		SDL_WINDOWPOS_CENTERED, //y
	//		640, 480,				//width, height
	//		SDL_WINDOW_SHOWN        //show the window
	//	);

	//	//3) Pass our window to the renderer
	//	if (_window != 0)
	//	{
	//		_renderer = SDL_CreateRenderer(
	//			_window,             //our window
	//			-1,                  //first 
	//			0                    //don't use any flag
	//			);
	//	}
	//}
	//else
	//{
	//	return -1;
	//}

	////4) Create and show window
	////Set renderer color to black
	//SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 255);

	////Declare variable
	//SDL_Texture* _texture;
	//SDL_Rect _destinationRect;
	//SDL_Rect _sourceRect;

	////Load image into surface
	//SDL_Surface* surface = IMG_Load("resources/cat.jpg");

	////Create a texture from an existing surface
	//_texture = SDL_CreateTextureFromSurface(_renderer, surface);
	//SDL_QueryTexture(_texture, nullptr, nullptr, &_sourceRect.w, &_sourceRect.h);

	////"Select" from image
	//_sourceRect.x = 0;
	//_sourceRect.y = 0;

	////Image position
	//_destinationRect.x = 0;
	//_destinationRect.y = 0;

	////Set dimensions of destination rect
	//_destinationRect.w = 640; // _sourceRect.w;
	//_destinationRect.h = 480; // _sourceRect.h;

	////Free surface
	//SDL_FreeSurface(surface);

	//while (true)
	//{
	//	//Clear window
	//	SDL_RenderClear(_renderer);

	//	//Render image here
	//	SDL_RenderCopy(_renderer, _texture, &_sourceRect, &_destinationRect);

	//	//Show the window
	//	SDL_RenderPresent(_renderer);
	//}

	//return 0;
}