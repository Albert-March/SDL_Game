#pragma once
#include "Scene.h"
#include "Spawner.h"

class Gameplay : public Scene
{
public:
	Gameplay() = default;
	void OnEnter() override
	{
		Object* o = new Object("resources/animation.png", Vector2(0.0f, 0.0f), Vector2(896.f, 64.f), false);
		o->GetRigidBody()->AddForce(Vector2(100, 100));
		SPAWN.SpawnObject(o);
	}

	void OnExit() override
	{

	}

	void Update() override
	{
		//DESTRUCTION


		//SPAWNING
		while (SPAWN.GetSpawnObjectsCount() > 0)
		{
			objects.push_back(SPAWN.GetSpawnedObject());
		}

		//UPDATING
		for (Object* o : objects)
		{
			o->Update();
		}
	}

	void Render() override
	{
		for (Object* o : objects)
		{
			o->Render();
		}
	}
};