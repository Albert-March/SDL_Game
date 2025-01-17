#pragma once
#include "Player.h"
#include "../ImageObject.h"
#include "../TimeManager.h"
#include "../InputManager.h"
#include "../Rigidbody.h"

enum PlayerState {
	Normal,
	Attack,
	Stuned
};

class PlayerSwatter : public Player {
public:
    float stateStartTime = 0.0f;
    PlayerState currentState = Normal;

    PlayerSwatter(Vector2 pos)
        : Player("resources/Swatter.png", pos, Vector2(1500.f, 1500.f)) {
    }

    void Update() override {
        switch (currentState) {
        case Normal:
            if (Input.GetLeftClick()) {
                currentState = Attack;
                stateStartTime = TIME.GetElapsedTime();
            }
            else {
                Movement();
            }
            break;

        case Stuned:
            float elapsedTime = TIME.GetElapsedTime() - stateStartTime;
            if (TIME.GetElapsedTime() - stateStartTime >= 2.0f) {
                currentState = Normal;
            }
            break;
        }

        std::cout << currentState;

        Player::Update();
    }

    void TransferLivesAndModeToDeath()
    {
        Death* deathScene = dynamic_cast<Death*>(SM.GetScene("Death"));
        deathScene->SetLivesAndMode(lives, 2);
    }

    void Movement() override {
        float mouseX = Input.GetMouseX();
        float mouseY = Input.GetMouseY();
        Vector2 mousePosition = Vector2(mouseX, mouseY);

        Vector2 direction = mousePosition - transform->position;

        float distanceSquared = direction.x * direction.x + direction.y * direction.y;

        if (distanceSquared < 1.0f) {
            return;
        }

        direction.Normalize();

        float maxSpeed = 1000.0f;
        float deltaTime = TIME.GetDeltaTime();
        Vector2 velocity = direction * maxSpeed * deltaTime;

        if (velocity.x * velocity.x + velocity.y * velocity.y > distanceSquared) {
            transform->position = mousePosition;
        }
        else {
            transform->position = transform->position + velocity;
        }
    }

    void OnCollisionEnter(Object* other) override {
        if (Enemy* enemy = dynamic_cast<Enemy*>(other)) {
            if (currentState == Attack) {
                AM.PlayClip("Impact", 0);
                enemy->Destroy();
                currentState = Normal;
            }
            else if (currentState == Stuned) {
                lives--;
                TransferLivesAndModeToDeath();
                SM.SetNextScene("Death");
            }
        }
        else {
            if (currentState == Attack)
            {
                currentState = Stuned;
            }
        }
        
        if (Bullet* bullet = dynamic_cast<Bullet*>(other)) {
            if (!bullet->IsFriendly()) {
                lives--;
                TransferLivesAndModeToDeath();
                SM.SetNextScene("Death");
            }
        }
    }

    void Render() override {
        Player::Render();
    }
};