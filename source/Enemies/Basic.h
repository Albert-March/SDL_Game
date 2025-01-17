#pragma once
#include "../Enemies/Enemy.h"
#include "../RenderManager.h"
#include "../Players/Bullet.h"
#include "../SpriteSelector.h"
#include "../AnimatedImageObject.h"

class Basic : public Enemy {
public:
	Basic(Vector2 pos, Player* player)
		: Enemy("resources/Enemies/" + SpriteSelector::GetSelectedEnemy(), pos, Vector2(1500.f, 1500.f)) {
	}

	void Update() override {
		Movement();
		Enemy::Update();
	}

	void Movement() override {
		Enemy::Movement();
	}

	void OnCollisionEnter(Object* other) override {
		if (Bullet* bullet = dynamic_cast<Bullet*>(other)) {
			if (bullet->IsFriendly()) {
				Destroy();
				other->Destroy();

				AnimatedImageObject* animated = new AnimatedImageObject("resources/Explosion.png", Vector2(0.f, 0.f), Vector2(626.f, 313.f), 4, 2, false);
				animated->GetTransform()->position = transform->position;
				animated->GetTransform()->scale = Vector2(0.5f, 0.5f);
				SPAWN.SpawnObject(animated);
			}
		}
	}

	void Render() override {
		Enemy::Render();
	}
};