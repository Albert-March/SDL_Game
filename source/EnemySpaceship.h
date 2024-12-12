#pragma once
#include "ImageObject.h"
#include "RenderManager.h"

class EnemySpaceship : public ImageObject {
public:

	EnemySpaceship(Vector2 pos, Vector2 startVelocity)
		: ImageObject("resources/PS_Enemy.png", Vector2(0.f, 0.f), Vector2(780.f, 660.f)) {

		transform->position = pos;
		transform->scale = Vector2(0.5f, 0.5f);
		physics->AddForce(startVelocity);
	}

	void Update() override {
		Movement();
		ImageObject::Update();
	}

	void Movement()
	{
		float halfWidth = transform->size.x * 0.5f * transform->scale.x;
		float enemyDist = transform->size.y * transform->scale.y;
		if (transform->position.x - halfWidth > RM->WINDOW_WIDTH) {
			transform->position.x = 0;
			transform->position.y += (enemyDist + 10);
		}
	}

	void OnCollisionEnter(Object* other) override {
		Destroy();
	}

	void Render() override {
		ImageObject::Render();
	}
};