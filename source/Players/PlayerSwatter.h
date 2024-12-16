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
    bool isColliding;
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

        case Attack:
            if (isColliding) {
                currentState = Normal;
            }
            else {
                float elapsedTime = TIME.GetElapsedTime() - stateStartTime;
                if (elapsedTime >= 0.2f) {
                    currentState = Stuned;
                    stateStartTime = TIME.GetElapsedTime();
                }
            }
            break;

        case Stuned:
            if (TIME.GetElapsedTime() - stateStartTime >= 2.0f) {
                currentState = Normal;
            }
            break;
        }

        Player::Update();
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
            isColliding = true;
            if (currentState == Attack) {
                enemy->Destroy();
                currentState = Normal;
            }
        }
        else {
            isColliding = false;
        }
        
        if (Enemy* enemy = dynamic_cast<Enemy*>(other)) {
            float currentTime = TIME.GetElapsedTime();

            //2 segons de cooldown
            if (currentTime - lastDamageTime >= 2.0f) {

                lives--;
                lastDamageTime = currentTime;

            }
        }
        if (Bullet* bullet = dynamic_cast<Bullet*>(other)) {
            if (!bullet->IsFriendly()) {
                float currentTime = TIME.GetElapsedTime();

                if (currentTime - lastDamageTime >= 2.0f) {

                    lives--;
                    lastDamageTime = currentTime;

                }
            }
        }
        if (lives <= 0) {
            Destroy();
            SM.SetNextScene("Splat");
            lives = 3; //Torna a comensar
        }
    }

    void Render() override {
        Player::Render();
    }
};