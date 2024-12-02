#pragma once
#include "Object.h"	
#include "RenderManager.h"

class TestObject : public Object
{
public:
	TestObject()
		:Object("resources/animation.png", Vector2(0.f, 0.f), Vector2(896.f, 64.f), false) {
		
		
		Vector2 randomPos = Vector2(rand() % RM->WINDOW_WIDTH, rand() % RM->WINDOW_HEIGHT);
		transform->position = randomPos;
		transform->scale = Vector2(0.2f, 0.2f);

		Vector2 randomForce = Vector2(-500 + rand() % 1001, -500 + rand() % 1001);
		physics->AddForce(Vector2(randomForce));
	}

	void OnCollisionEnter(Object* other) override {

		if (TestObject* to = reinterpret_cast<TestObject*>(other)) {

		}
	}

};