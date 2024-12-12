#pragma once
#include "Scene.h"
#include "Spawner.h"
#include "TestObject.h"
#include "TextObject.h"
#include "PlayerSpaceship.h"
#include "EnemySpaceship.h"
#include "AudioManager.h"
#include "InputManager.h"

class Gameplay : public Scene
{
public:
	Gameplay() = default;

	void OnEnter() override
	{
		SPAWN.SpawnObject(new PlayerSpaceship(Vector2(RM->WINDOW_WIDTH/2, RM->WINDOW_HEIGHT-100)));
		for (int i = 0; i < 50; i++) {
			SPAWN.SpawnObject(new EnemySpaceship(Vector2(50, 40), Vector2(10000, 0)));

		}

		//Crea un text object que digui "Hola" a la posicio (100, 100)
		/*Object* textObj = new TextObject("Tocafi CALVOOO");
		textObj->GetTransform()->position = Vector2(100, 100);
		SPAWN.SpawnObject(textObj);*/

		//audio
		AM.LoadSong("discord-notification");
		AM.PlaySong("discord-notification");

		AM.LoadClip("shrek");
		

	}

	void Update() override
	{
		Scene::Update();
		if(Input.GetEvent(SDLK_SPACE, DOWN))
			AM.PlayClip("shrek", 0);
	}

	void SpawnObjectRandomly() {		
		SPAWN.SpawnObject(new TestObject());
	}
};