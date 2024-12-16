#pragma once
#include "../Enemies/Enemy.h"
#include "../RenderManager.h"
#include <cmath>

class Seeker : public Enemy {
private:
    Player* playerReference;
    float detectionRange = 300.0f;
    bool followPlayer = false;

public:
	Seeker(Vector2 pos, Player* player)
		: Enemy("resources/PS_Enemy.png", pos, Vector2(1500.f, 1500.f)) {
        playerReference = player;
	}

    void Update() override {

        if (IsPlayerInRange(playerReference)) {
            followPlayer = true;
        }
        if (followPlayer == true) {
            FollowPlayer(playerReference);
        }
        else {
            Movement();
        }

        Enemy::Update();
    }

    bool IsPlayerInRange(Player* playerReference) {
        if (!playerReference) return false;

        Vector2 playerPos = playerReference->GetTransform()->position;
        Vector2 seekerPos = transform->position;

        float dx = playerPos.x - seekerPos.x;
        float dy = playerPos.y - seekerPos.y;
        float distance = std::sqrt(dx * dx + dy * dy);

        return distance <= detectionRange;
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

    void FollowPlayer(Player* playerReference) {
        Vector2 playerPos = playerReference->GetTransform()->position;
        Vector2 seekerPos = transform->position;
        Vector2 direction = playerPos - seekerPos;

        direction.Normalize();

        float speed = 200.0f * TIME.GetDeltaTime();
        transform->position = transform->position + direction * speed;
    }

    void Movement() override {
        Enemy::Movement();
    }
};