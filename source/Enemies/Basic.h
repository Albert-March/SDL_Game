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

				std::string VFX = SpriteSelector::GetSelectedVFX();
				int VFXframeWidth = SpriteSelector::GetVFXframeWidth();
				int VFXframeHeight = SpriteSelector::GetVFXframeHeight();
				int VFXNumRows = SpriteSelector::GetVFXNumRows();
				int VFXNumColumns = SpriteSelector::GetVFXNumColumns();
				AnimatedImageObject* animated = new AnimatedImageObject("resources/VFX/" + VFX, Vector2(0.f, 0.f), Vector2(VFXframeWidth, VFXframeHeight), VFXNumRows, VFXNumColumns, false);
				animated->GetTransform()->position = transform->position;
				animated->GetTransform()->scale = Vector2(1.0f, 1.0f);
				SPAWN.SpawnObject(animated);
			}
		}
	}

	int GetScoreValue() const override { return 100; }

	void Render() override {
		Enemy::Render();
	}
};