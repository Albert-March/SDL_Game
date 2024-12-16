#include "Game.h"
#include "RenderManager.h"
#include "TimeManager.h"
#include "GameplaySpaceInvaders.h"
#include "GameplayTanks.h"
#include "GameplaySwatter.h"
#include "SceneManager.h"
#include "MainMenu.h"

void Game::Init()
{
	RM->Init();

	RM->LoadTexture("resources/bullet.png");
	RM->LoadTexture("resources/PS_Enemy.png");
	RM->LoadTexture("resources/Tank.png");
	RM->LoadTexture("resources/Spaceship.png");
	RM->LoadTexture("resources/Swatter.png");
	RM->LoadTexture("resources/Cannon.png");
	RM->LoadTexture("resources/animation.png");

	assert(SM.AddScene("Main Menu", new MainMenu()));

	assert(SM.AddScene("SpaceInvaders", new GameplaySpaceInvaders()));
	assert(SM.AddScene("Tanks", new GameplayTanks()));
	assert(SM.AddScene("Splat", new GameplaySwatter()));

	assert(SM.InitFirstScene("Main Menu"));
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
	//SM.GetCurrentScene()->OnEnter();

	RM->Release();
}
