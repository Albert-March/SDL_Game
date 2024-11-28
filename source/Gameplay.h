#pragma once
#include "Scene.h"

class Gameplay : public Scene
{
public:
	Gameplay() = default;
	void OnEnter() override
	{
		objects.push_back(Object("resources/animation.png", Vector2(0.0f, 0.0f), Vector2(896.f, 64.f), false));
		objects[0].GetRigidBody()->AddForce(Vector2(100, 100));
	}

	void OnExit() override
	{

	}

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
	}
};