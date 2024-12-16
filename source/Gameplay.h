#pragma once
#include "Scene.h"
#include "Spawner.h"
#include "TestObject.h"
#include "TextObject.h"

#include "../source/Players/PlayerSpaceship.h"
#include "../source/Players/PlayerTank.h"
#include "../source/Players/PlayerSwatter.h"

#include "../source/Enemies/Enemy.h"
#include "../source/Enemies/Basic.h"
#include "../source/Enemies/Seeker.h"
#include "../source/Enemies/Shooting.h"
#include "../source/Enemies/Aiming.h"
#include "../source/Enemies/Exploding.h"

#include "AudioManager.h"
#include "InputManager.h"

class Gameplay : public Scene
{
private:
	float lastSpawnTime = -5.0f;
	float spawnCooldown = 5.0f;

	int gameMode = 2;
	int enemies = 4;

	Player* activePlayer = nullptr;

public:
	Gameplay() = default;

	void OnEnter() override
	{
		//UI
		Object* textObj = new TextObject("Buscam");
		textObj->GetTransform()->position = Vector2(100, 100);
		SPAWN.SpawnObject(textObj);

		switch (gameMode)
		{
		case 1:
			//PlayerSpaceship
			activePlayer = new PlayerSpaceship(Vector2(RM->WINDOW_WIDTH / 2, RM->WINDOW_HEIGHT - 100));
			break;
		case 2:
			//PLayerTank
			activePlayer = new PlayerTank(Vector2(RM->WINDOW_WIDTH / 2, RM->WINDOW_HEIGHT - 100));
			break;
		case 3:
			//PlayerSwatter
			activePlayer = new PlayerSwatter(Vector2(RM->WINDOW_WIDTH / 2, RM->WINDOW_HEIGHT - 100));
			break;
		}
		if (activePlayer) {
			SPAWN.SpawnObject(activePlayer);
		}
	}


	void Update() override {
		float currentTime = TIME.GetElapsedTime();

		if (currentTime - lastSpawnTime >= spawnCooldown) {
			SpawnEnemy();
			lastSpawnTime = currentTime;
		}
		Scene::Update();
	}

private:
	void SpawnEnemy() {
		switch (enemies) {
		case 1:
			SPAWN.SpawnObject(new Basic(Vector2(50, 40), activePlayer));
			break;
		case 2:
			SPAWN.SpawnObject(new Seeker(Vector2(50, -20), activePlayer));
			break;
		case 3:
			//SPAWN.SpawnObject(new Shooting(Vector2(50, 40), activePlayer));
			break;
		case 4:
			SPAWN.SpawnObject(new Aiming(Vector2(50, 40), activePlayer));
			break;
		case 5:
			//SPAWN.SpawnObject(new Exploding(Vector2(50, 40), activePlayer));
			break;
		}
	}

		
		//audio
		//AM.LoadSong("discord-notification");
		//AM.PlaySong("discord-notification");

		//AM.LoadClip("shrek");


	/*void Update() override
	{
		Scene::Update();
		if(Input.GetEvent(SDLK_SPACE, DOWN))
			AM.PlayClip("shrek", 0);
	}*/
};