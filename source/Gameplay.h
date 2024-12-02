#pragma once
#include "Scene.h"
<<<<<<< Updated upstream
=======
#include "Spawner.h"
#include "TestObject.h"
>>>>>>> Stashed changes

class Gameplay : public Scene
{
public:
	Gameplay() = default;
	void OnEnter() override
	{
<<<<<<< Updated upstream
		objects.push_back(Object("resources/animation.png", Vector2(0.0f, 0.0f), Vector2(896.f, 64.f), false));
		objects[0].GetRigidBody()->AddForce(Vector2(100, 100));
=======
		for(int i = 0; i < 50; i++)
		SpawnObjectRandomly();
>>>>>>> Stashed changes
	}

	void SpawnObjectRandomly() {

		SPAWN.SpawnObject(new TestObject());
	}

<<<<<<< Updated upstream
	void Update() override
	{
		for (Object o : objects)
		{
			o.Update();
		}
	}

	void Render() override
	{
		for (Object o : objects)
		{
			o.Render();
		}
=======
	void OnExit() override {
		Scene::OnExit();
	}

	void Update() override {
		Scene::Update();
	//	objects[0]->Destroy();
		//SpawnObjectRandomly();
	}

	void Render() override {
		Scene::Render();
>>>>>>> Stashed changes
	}
};