#include "Game.h"
#include "RenderManager.h"
#include "TimeManager.h"
#include "Gameplay.h"
#include "SceneManager.h"
#include "MainMenu.h"

void Game::Init()
{
	RM->Init();

	RM->LoadTexture("resources/cat.jpg");

	assert(SM.AddScene("Main Menu", new MainMenu()));
	assert(SM.AddScene("Gameplay", new Gameplay()));

	assert(SM.InitFirstScene("Gameplay"));
}

void Game::Update()
{	
	SM.UpdateCurrentScene();
}

void Game::Render()
{
	RM->ClearScreen();

	SM.GetCurrentScene()->Render();

	RM->RenderScreen();
}

void Game::Release()
{
	SM.GetCurrentScene()->OnEnter();

	RM->Release();
}
