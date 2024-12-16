#pragma once
#include "Scene.h"
#include "Spawner.h"
#include "TextObject.h"

#include "../source/Players/PlayerSpaceship.h"

#include "../source/Enemies/Enemy.h"
#include "../source/Enemies/Basic.h"
#include "../source/Enemies/Seeker.h"
#include "../source/Enemies/Shooting.h"
#include "../source/Enemies/Aiming.h"
#include "../source/Enemies/Exploding.h"

#include "AudioManager.h"
#include "InputManager.h"
#include "SceneManager.h"

class GameplaySpaceInvaders : public Scene
{
private:
	float lastSpawnTime = -5.0f;
	float spawnCooldown = 5.0f;

	Player* activePlayer = nullptr;
	int playerLives = 3;
	int enemyType;

public:
	GameplaySpaceInvaders() = default;

	void OnEnter() override {
		activePlayer = new PlayerSpaceship(Vector2(RM->WINDOW_WIDTH / 2, RM->WINDOW_HEIGHT - 100));
		SPAWN.SpawnObject(activePlayer);
	}

	void Update() override {
		float currentTime = TIME.GetElapsedTime();

		if (currentTime - lastSpawnTime >= spawnCooldown) {
			enemyType = 4; // = rand() % 2 + 1;
			SpawnEnemy();
			lastSpawnTime = currentTime;
		}
		playerLives = activePlayer->lives;

		if (Input.GetEvent(SDLK_2, DOWN))
			SM.SetNextScene("Tanks");
		if (Input.GetEvent(SDLK_3, DOWN))
			SM.SetNextScene("Splat");

		Scene::Update();
	}

	void Render() override {
		Scene::Render();
	}

private:
	void SpawnEnemy() {
		switch (enemyType) {
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
};
