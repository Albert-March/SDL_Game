#pragma once
#include "../Enemies/Enemy.h"
#include "../RenderManager.h"
#include "EnemyBullet.h"

class Aiming : public Enemy {
private:
	Player* playerReference;
	float lastShotTime = 0.0f;
	const float shootCooldown = 2.0f;

public:
	Aiming(Vector2 pos, Player* player)
		: Enemy("resources/PS_Enemy.png", pos, Vector2(1500.f, 1500.f)) {
		playerReference = player;
	}

	void Update() override {
		Movement();
		Shoot();
		Enemy::Update();
	}

	void Movement() override {
		Enemy::Movement();
	}

	void Shoot() {
		Vector2 playerPos = playerReference->GetTransform()->position;
		Vector2 aimingPos = transform->position;			
		Vector2 direction = playerPos - aimingPos;
		direction.Normalize();

		float halfEnemySizeY = transform->size.y * 0.5f;

		Vector2 edgePosition = CalculateEdgePosition(aimingPos, direction, halfEnemySizeY);

		float bulletSpeed = 8000.0f;
		Vector2 bulletVelocity = direction * bulletSpeed;

		float angleRadians = atan2(direction.y, direction.x);
		float angleDegrees = angleRadians * (180.0f / M_PI);
		angleDegrees -= 90.0f;

		EnemyBullet* bullet = new EnemyBullet(edgePosition, bulletVelocity);

		bullet->SetRotation(angleDegrees);

		SPAWN.SpawnObject(bullet);
	}

	Vector2 CalculateEdgePosition(const Vector2& center, const Vector2& direction, float halfSize) {
		float slope = (direction.y != 0) ? direction.x / direction.y : 0; //Si y es zero la divisio es indefinida, aixo asegura que almenys el pendent sigui 0

		if (fabs(direction.y) > fabs(direction.x)) {     //fabs retorna valor avsolut. Per comprovar quin eix de la direccio es mes gran
			//Direccio Vertical mes gran
			float yOffset = (direction.y > 0) ? halfSize : -halfSize;
			float xOffset = slope * yOffset;
			return Vector2(center.x + xOffset, center.y + yOffset);
		}
		else {
			//Direccio Horitzontal mes gran
			float xOffset = (direction.x > 0) ? halfSize : -halfSize;
			float yOffset = (direction.y != 0) ? (1 / slope) * xOffset : 0;
			return Vector2(center.x + xOffset, center.y + yOffset);
		}
	}

	void OnCollisionEnter(Object* other) override {
		if (PlayerBullet* to = dynamic_cast<PlayerBullet*>(other)) {
			Destroy();
			other->Destroy();
		}
	}

	void Render() override {
		Enemy::Render();
	}
};