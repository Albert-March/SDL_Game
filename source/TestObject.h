#pragma once
#include "Object.h"
#include "RenderManager.h"

class TestObject : public Object {
public:
	TestObject()
		: Object("resources/cat.jpg", Vector2(0.0f, 0.0f), Vector2(1500.f, 1500.f), false) {

		//RAND IN ALL THE WINDOW
		Vector2 randomPos = Vector2(rand() % RM->WINDOW_WIDTH, rand() % RM->WINDOW_HEIGHT);
		transform->position = randomPos;
		transform->scale = Vector2(0.2f, 0.2f);

		Vector2 randomForce = Vector2(-5000 + rand() % 10001, -5000 + rand() % 10001);
		physics->AddForce(randomForce);
	}

	void OnCollisionEnter(Object* other) override {
		if (TestObject* to = dynamic_cast<TestObject*>(other)) {
			
		}
	}
};