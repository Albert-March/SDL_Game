#include "Game.h"
#include "RenderManager.h"
#include "TimeManager.h"
#include "Gameplay.h"

void Game::Init()
{
	RM->Init();

	gameplayTest = new Gameplay();
	gameplayTest->OnEnter();
}

void Game::Update()
{	
	gameplayTest->Update();
}

void Game::Render()
{
	RM->ClearScreen();

	gameplayTest->Render();

	RM->RenderScreen();
}

void Game::Release()
{
	gameplayTest->OnEnter();

	RM->Release();
}
