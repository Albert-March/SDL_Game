#pragma once
#include "Scene.h"
#include "Spawner.h"
#include "TestObject.h"

class Gameplay : public Scene
{
public:
	Gameplay() = default;

	void OnEnter() override
	{
		/*for(int i = 0; i<50; i++)
			SpawnObjectRandomly();*/

		objects.push_back(new TestObject(Vector2(100, 100), Vector2(1000, 0)));
		objects.push_back(new TestObject(Vector2(500, 100), Vector2(-1000, 0)));
	}

	void SpawnObjectRandomly() {		
		SPAWN.SpawnObject(new TestObject());
	}
};