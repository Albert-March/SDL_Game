#pragma once
#include "Object.h"
#include <vector>
#include "Spawner.h"

class Scene
{
protected:
	std::vector<Object*> ui;
	std::vector<Object*> objects;

public:
	Scene() = default;
	virtual void OnEnter() = 0;
	virtual void OnExit() {
		//Clear the spawner
		SPAWN.ClearSpawnedObjects();
		//Destroy ALL the objects
		for (Object* o : objects)
			delete o;
		objects.clear();
	}
	virtual void Update() {
		//DESTRUCTION
		for (int i = objects.size() - 1; i >= 0; i--) {
			if (objects[i]->IsPendingDestroy()) {
				delete objects[i];
				objects.erase(objects.begin() + i);
			}
		}

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
	virtual void Render() {
		for (Object* o : objects)
		{
			o->Render();
		}
	}
};