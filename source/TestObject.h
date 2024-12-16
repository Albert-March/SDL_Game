#pragma once
#include "ImageObject.h"
#include "RenderManager.h"

class TestObject : public ImageObject {
public:
	TestObject()
		: ImageObject("resources/cat.jpg", Vector2(0.0f, 0.0f), Vector2(1500.f, 1500.f)) {

		//RAND IN ALL THE WINDOW
		Vector2 randomPos = Vector2(rand() % RM->WINDOW_WIDTH, rand() % RM->WINDOW_HEIGHT);
		transform->position = randomPos;
		transform->rotation = 30.0f;
		transform->scale = Vector2(1.f, 1.f);

		Vector2 randomForce = Vector2(-5000 + rand() % 10001, -5000 + rand() % 10001);
		physics->AddForce(randomForce);
	}

	TestObject(Vector2 pos, Vector2 startVelocity)
		: ImageObject("resources/cat.jpg", Vector2(0.f, 0.f), Vector2(1500.f, 1500.f)) {

		transform->position = pos;
		//physics->AddTorque(3000.0f);
		transform->scale = Vector2(1.f, 1.f);
		physics->AddForce(startVelocity);
	}

	void OnCollisionEnter(Object* other) override {
		Destroy();
	}
};