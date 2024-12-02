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
		for(int i = 0; i<50; i++)
			SpawnObjectRandomly();
	}

	void SpawnObjectRandomly() {		
		SPAWN.SpawnObject(new TestObject());
	}
	void OnExit() override
	{
		Scene::OnExit();
	}

	void Update() override
	{
		Scene::Update();
		SpawnObjectRandomly();
	}

	void Render() override
	{
		Scene::Render();
	}
};