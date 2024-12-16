#pragma once
#include "../Enemies/Enemy.h"
#include "../RenderManager.h"

class Shooting : public Enemy {

public:
	Shooting(Vector2 pos, Player* player)
		: Enemy("resources/PS_Enemy.png", pos, Vector2(1500.f, 1500.f)) {
	}

	void Update() override {
		Movement();
		Enemy::Update();
	}

	void Movement() override {
		Enemy::Movement();
	}

	void OnCollisionEnter(Object* other) override {
		if (PlayerBullet* to = reinterpret_cast<PlayerBullet*>(other)) {
			Destroy();
			other->Destroy();
		}
	}

	void Render() override {
		Enemy::Render();
	}
};