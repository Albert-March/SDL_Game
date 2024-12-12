#pragma once
#include "ImageObject.h"
#include "RenderManager.h"

class Bullet : public ImageObject {
public:

	Bullet(Vector2 pos, Vector2 startVelocity)
		: ImageObject("resources/bullet.png", Vector2(0.f, 0.f), Vector2(200.f, 500.f)) {

		transform->position = pos;
		transform->scale = Vector2(1.f, 1.f);
		physics->AddForce(startVelocity);
	}

	void Update() override {
		ImageObject::Update();
	}

	void OnCollisionEnter(Object* other) override {
		Destroy();
	}

	void Render() override {
		ImageObject::Render();
	}
};