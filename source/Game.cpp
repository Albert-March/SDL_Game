#include "Game.h"
#include "RenderManager.h"
#include "TimeManager.h"
#include "GameplaySpaceInvaders.h"
#include "GameplayTanks.h"
#include "GameplaySwatter.h"
#include "SceneManager.h"
#include "SplashScreen.h"
#include "MainMenu.h"
#include "PlayMenu.h"
#include "SpriteSelector.h"
#include "SaveScore.h"
#include "Death.h"
#include "Ranking.h"

void Game::Init()
{
	RM->Init();

	RM->LoadTexture("resources/bullet.png");
	RM->LoadTexture("resources/Tank.png");
	RM->LoadTexture("resources/Spaceship.png");
	RM->LoadTexture("resources/Swatter.png");
	RM->LoadTexture("resources/Cannon.png");
	RM->LoadTexture("resources/SplashScreen.png");
	RM->LoadTexture("resources/LoadingImage.png");
	RM->LoadTexture("resources/MenuBackground.png");

	RM->LoadTexture("resources/selected.png");
	RM->LoadTexture("resources/Backgrounds/background_1.jpg");
	RM->LoadTexture("resources/Backgrounds/background_2.jpg");
	RM->LoadTexture("resources/Backgrounds/background_3.jpg");

	RM->LoadTexture("resources/Enemies/enemy_1.png");
	RM->LoadTexture("resources/Enemies/enemy_2.png");
	RM->LoadTexture("resources/Enemies/enemy_3.png");
	RM->LoadTexture("resources/Enemies/enemySS_1.png");
	RM->LoadTexture("resources/Enemies/enemySS_2.png");
	RM->LoadTexture("resources/Enemies/enemySS_3.png");

	RM->LoadTexture("resources/VFX/VFX_1.png");
	RM->LoadTexture("resources/VFX/VFX_2.png");
	RM->LoadTexture("resources/VFX/VFX_3.png");
	RM->LoadTexture("resources/VFX/VFXSS_1.png");
	RM->LoadTexture("resources/VFX/VFXSS_2.png");
	RM->LoadTexture("resources/VFX/VFXSS_3.png");

	assert(SM.AddScene("Splash Screen", new SplashScreen()));

	assert(SM.AddScene("Main Menu", new MainMenu()));
	assert(SM.AddScene("PlayMenu", new PlayMenu()));
	assert(SM.AddScene("SpriteSelector", new SpriteSelector()));
	assert(SM.AddScene("Ranking", new Ranking()));

	assert(SM.AddScene("SpaceInvaders", new GameplaySpaceInvaders()));
	assert(SM.AddScene("Tanks", new GameplayTanks()));
	assert(SM.AddScene("Swatter", new GameplaySwatter()));

	assert(SM.AddScene("SaveScore", new SaveScore()));
	assert(SM.AddScene("Death", new Death()));


	assert(SM.InitFirstScene("Main Menu"));


	//audio
	AM.LoadClip("SelectButton");
	AM.LoadClip("ClickButton");
	AM.LoadClip("StartGame");
	AM.LoadClip("Shot");
	AM.LoadClip("Impact");

	AM.LoadSong("Music");

	AM.PlaySong("Music");
	AM.SetMusicVolume(20);

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
