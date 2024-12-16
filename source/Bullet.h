#pragma once
#include "ImageObject.h"
#include "RenderManager.h"

class Bullet : public ImageObject {
public:

	Bullet(Vector2 pos, Vector2 startVelocity)
		: ImageObject("resources/bullet.png", Vector2(0.f, 0.f), Vector2(1200.f, 1200.f)) {

		transform->position = pos;
		transform->scale = Vector2(0.1f, 0.1f);
		physics->AddForce(startVelocity);
	}

	void SetRotation(float rotation) {
		transform->rotation = rotation;
	}

	void Update() override {
		ImageObject::Update();
	}

	void OnCollisionEnter(Object* other) override {
		
	}

	void Render() override {
		ImageObject::Render();
	}
};