#pragma once
#include "Scene.h"
#include "Spawner.h"
#include "TestObject.h"
#include "TextObject.h"
#include "PlayerSpaceship.h"

class Gameplay : public Scene
{
public:
	Gameplay() = default;

	void OnEnter() override
	{
		/*for(int i = 0; i<50; i++)
			SpawnObjectRandomly();*/

		SPAWN.SpawnObject(new PlayerSpaceship(Vector2(RM->WINDOW_WIDTH/2, RM->WINDOW_HEIGHT-100)));
		//SPAWN.SpawnObject(new TestObject(Vector2(500, 100), Vector2(-1000, 0)));

		//Crea un text object que digui "Hola" a la posicio (100, 100)
		/*Object* textObj = new TextObject("Tocafi CALVOOO");
		textObj->GetTransform()->position = Vector2(100, 100);
		SPAWN.SpawnObject(textObj);*/
	}

	void SpawnObjectRandomly() {		
		SPAWN.SpawnObject(new TestObject());
	}
};