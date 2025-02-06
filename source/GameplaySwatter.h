#pragma once
#include "Scene.h"
#include "Spawner.h"
#include "TextObject.h"

#include "../source/Players/PlayerSwatter.h"

#include "../source/Enemies/Enemy.h"
#include "../source/Enemies/Basic.h"
#include "../source/Enemies/Seeker.h"
#include "../source/Enemies/Shooting.h"
#include "../source/Enemies/Aiming.h"
#include "../source/Enemies/Exploding.h"

#include "AudioManager.h"
#include "InputManager.h"
#include "SceneManager.h"

class GameplaySwatter : public Scene
{
private:
	float lastSpawnTime = -2.0f;
	float spawnCooldown = 2.0f;

	Player* activePlayer = nullptr;
	int playerLives = 3;
	int enemyType;


	TextObject* livesText;
	TextObject* scoreText;
	int score = 0;

	std::vector<Enemy*> activeEnemies;
	int enemiesSpawned = 0;

public:
	GameplaySwatter() = default;

	void OnEnter() override {
		activeEnemies.clear();

		std::string background = SpriteSelector::GetSelectedBackground();
		ImageObject* bg = new ImageObject("resources/Backgrounds/" + background, Vector2(0.f, 0.f), Vector2(1360.f, 768.f));
		bg->GetTransform()->position = Vector2(RM->WINDOW_WIDTH / 2, RM->WINDOW_HEIGHT / 2);
		bg->GetTransform()->scale = Vector2(13.6f, 7.68f);
		SPAWN.SpawnObject(bg);

		activePlayer = new PlayerSwatter(Vector2(RM->WINDOW_WIDTH / 2, RM->WINDOW_HEIGHT - 100));
		SPAWN.SpawnObject(activePlayer);

		InitUI();
	}

	void TransferScoreAndModeToWin() {
		SaveScore* saveScore = dynamic_cast<SaveScore*>(SM.GetScene("SaveScore"));
		saveScore->SetScoreAndMode(score, 2);
	}

	void AddScore(int points) {
		score += points;
	}

	void Update() override {
		float currentTime = TIME.GetElapsedTime();

		if (enemiesSpawned < 10 && (currentTime - lastSpawnTime >= spawnCooldown)) {
			enemyType = rand() % 3 + 1;
			SpawnEnemy();
			lastSpawnTime = currentTime;
			enemiesSpawned++;
		}
		if (enemiesSpawned >= 10) {
			TransferScoreAndModeToWin();
			SM.SetNextScene("SaveScore");
		}

		for (auto it = activeEnemies.begin(); it != activeEnemies.end(); ) {
			if ((*it)->IsPendingDestroy()) {
				AddScore((*it)->GetScoreValue());
				it = activeEnemies.erase(it);
			}
			else {
				++it;
			}
		}

		playerLives = activePlayer->lives;
		livesText->SetText("Lives: " + std::to_string(playerLives));

		scoreText->SetText("Score: " + std::to_string(score));

		if (Input.GetEvent(SDLK_ESCAPE, DOWN))
			SM.SetNextScene("Main Menu");

		Scene::Update();
	}

	void Render() override {
		Scene::Render();
	}

private:
	void SpawnEnemy() {
		Enemy* newEnemy = nullptr;

		switch (enemyType) {
		case 1:
			newEnemy = new Basic(Vector2(50, 40), activePlayer);
			break;
		case 2:
			newEnemy = new Seeker(Vector2(50, -20), activePlayer);
			break;
		case 3:
			newEnemy = new Aiming(Vector2(50, 40), activePlayer);
			break;
			/*case 4:
				newEnemy = new Shooting(Vector2(50, 40), activePlayer);
				break;
			case 5:
				newEnemy = new Exploding(Vector2(50, 40), activePlayer);
				break;*/
		}

		if (newEnemy) {
			SPAWN.SpawnObject(newEnemy);
			activeEnemies.push_back(newEnemy);
		}
	}

	void InitUI() {
		// Título del juego
		TextObject* title = new TextObject("SWATTER");
		title->GetTransform()->position = Vector2(RM->WINDOW_WIDTH - 200, 100.0f);
		title->GetTransform()->scale = Vector2(1.5f, 1.5f);
		SPAWN.SpawnObject(title);


		// Vidas del jugador
		livesText = new TextObject("Lives: " + std::to_string(playerLives));
		livesText->GetTransform()->position = Vector2(RM->WINDOW_WIDTH - 200, 200.0f);
		livesText->GetTransform()->scale = Vector2(1.5f, 1.5f);

		SPAWN.SpawnObject(livesText);

		// Puntuación
		scoreText = new TextObject("Score: " + std::to_string(score));
		scoreText->GetTransform()->position = Vector2(RM->WINDOW_WIDTH - 200, 150.0f);
		scoreText->GetTransform()->scale = Vector2(1.5f, 1.5f);


		SPAWN.SpawnObject(scoreText);
	}
};