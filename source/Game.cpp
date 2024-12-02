#include "Game.h"
#include "RenderManager.h"
#include "TimeManager.h"
#include "Gameplay.h"

void Game::Init()
{
	RM->Init();

<<<<<<< Updated upstream
	gameplayTest = new Gameplay();
	gameplayTest->OnEnter();
=======
	RM->LoadTexture("resources/animation.png");

	assert(SM.AddScene("Main Menu", new MainMenu()));
	assert(SM.AddScene("Gameplay", new Gameplay()));

	assert(SM.InitFirstScene("Gameplay"));
>>>>>>> Stashed changes
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
