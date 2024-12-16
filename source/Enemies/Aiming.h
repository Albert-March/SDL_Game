#pragma once
#include "../Enemies/Enemy.h"
#include "../RenderManager.h"
#include "../Players/Bullet.h"

class Aiming : public Enemy {
private:
	Player* playerReference;
	float phaseStartTime = 0.0f;
	float stopDuration = 2.0f;
	float moveDuration = 4.0f;
	bool isStopped = false;

public:
	Aiming(Vector2 pos, Player* player)
		: Enemy("resources/PS_Enemy.png", pos, Vector2(1500.f, 1500.f)) {
		playerReference = player;
	}

	void Update() override {
		float currentTime = TIME.GetElapsedTime();

		if (isStopped) {
			if (currentTime - phaseStartTime >= stopDuration) {
				isStopped = false;
				phaseStartTime = currentTime;
			}
		}
		else {
			if (currentTime - phaseStartTime >= moveDuration) {
				isStopped = true;
				Shoot();
				phaseStartTime = currentTime;
			}
			else {
				Movement();
			}
		}

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

		Bullet* bullet = new Bullet(edgePosition, bulletVelocity, 0);

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
		if (Bullet* bullet = dynamic_cast<Bullet*>(other)) {
			if (bullet->IsFriendly()) {
				
				Destroy();
				other->Destroy();
			}	
		}
	}

	void Render() override {
		Enemy::Render();
	}
};