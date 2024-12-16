#pragma once
#include "Player.h"
#include "../ImageObject.h"
#include "../RenderManager.h"
#include "../TimeManager.h"
#include "../Players/Bullet.h"

class Cannon : public ImageObject {
public:
    Cannon(Vector2 pos)
        : ImageObject("resources/Cannon.png", Vector2(0.f, 0.f), Vector2(500.f, 500.f)) {
        transform->position = pos;
        transform->rotation = 0.0f;
        transform->scale = Vector2(1.f, 1.f);
    }

    void SetPosition(Vector2 position) {
        transform->position = position;
    }

    void SetRotation(float rotation) {
        transform->rotation = rotation;
    }

    Vector2 GetSize() {
        return transform->size * transform->scale;
    }

    void Update() override {
		ImageObject::Update();
	}

	void Render() override {
		ImageObject::Render();
	}
};

class PlayerTank : public Player {
private:
    Cannon* cannon = new Cannon(transform->position); 

    float lastShotTime = 0.0f;
    const float shootCooldown = 1.0f;

public:

    PlayerTank(Vector2 pos)
        : Player("resources/Tank.png", pos, Vector2(500.f, 500.f)) {
        SPAWN.SpawnObject(cannon);
    }

    void Update() override {
        Movement();
        cannon->SetPosition(transform->position);
        cannon->SetRotation(CalculateAngle() + 180.f);
        Shooting();

        Player::Update();
    }

    void Movement() {
        float speed = 10.0f;
        if (Input.GetEvent(SDLK_UP, HOLD) || Input.GetEvent(SDLK_w, HOLD)) {
            transform->position.y -= speed;
            transform->rotation = 0.0f;
        }
        if (Input.GetEvent(SDLK_DOWN, HOLD) || Input.GetEvent(SDLK_s, HOLD)) {
            transform->position.y += speed;
            transform->rotation = 180.0f;
        }
        if (Input.GetEvent(SDLK_LEFT, HOLD) || Input.GetEvent(SDLK_a, HOLD)) {
            transform->position.x -= speed;
            transform->rotation = 270.0f;
        }
        if (Input.GetEvent(SDLK_RIGHT, HOLD) || Input.GetEvent(SDLK_d, HOLD)) {
            transform->position.x += speed;
            transform->rotation = 90.0f;
        }
        if (Input.GetEvent(SDLK_UP, HOLD) && Input.GetEvent(SDLK_LEFT, HOLD) || Input.GetEvent(SDLK_w, HOLD) && Input.GetEvent(SDLK_a, HOLD)) {
            transform->rotation = 315.0f;
        }
        if (Input.GetEvent(SDLK_UP, HOLD) && Input.GetEvent(SDLK_RIGHT, HOLD) || Input.GetEvent(SDLK_w, HOLD) && Input.GetEvent(SDLK_d, HOLD)) {
            transform->rotation = 45.0f;
        }
        if (Input.GetEvent(SDLK_DOWN, HOLD) && Input.GetEvent(SDLK_LEFT, HOLD) || Input.GetEvent(SDLK_s, HOLD) && Input.GetEvent(SDLK_a, HOLD)) {
            transform->rotation = 225.0f;
        }
        if (Input.GetEvent(SDLK_DOWN, HOLD) && Input.GetEvent(SDLK_RIGHT, HOLD) || Input.GetEvent(SDLK_s, HOLD) && Input.GetEvent(SDLK_d, HOLD)) {
            transform->rotation = 135.0f;
        }

        float halfWidth = transform->size.x * 0.5f * transform->scale.x;
        if (transform->position.x - halfWidth < 0) {
            transform->position.x = halfWidth;
        }
        if (transform->position.x + halfWidth > RM->WINDOW_WIDTH) {
            transform->position.x = RM->WINDOW_WIDTH - halfWidth;
        }
        float halfHeight = transform->size.y * 0.5f * transform->scale.y;
        if (transform->position.y - halfHeight < 0) {
            transform->position.y = halfHeight;
        }
        if (transform->position.y + halfHeight > RM->WINDOW_HEIGHT) {
            transform->position.y = RM->WINDOW_HEIGHT - halfHeight;
        }
    }    

    void Shooting() {
        float currentTime = TIME.GetElapsedTime();

        if (Input.GetEvent(SDLK_SPACE, DOWN)) {
            FireBullet();
            lastShotTime = currentTime;
        }
        if (Input.GetEvent(SDLK_SPACE, HOLD) && currentTime - lastShotTime >= shootCooldown) {
            FireBullet();
            lastShotTime = currentTime;
        }
    }

    int CalculateAngle()
    {
        float mouseX = Input.GetMouseX();
        float mouseY = Input.GetMouseY();
        Vector2 mousePosition = Vector2(mouseX, mouseY);

        Vector2 playerPosition = transform->position;

        Vector2 direction = mousePosition - playerPosition;
        direction.Normalize();

        float angleRadians = atan2(direction.y, direction.x);
        float angleDegrees = angleRadians * (180.0f / M_PI);
        angleDegrees -= 90.0f;

        return angleDegrees;
    }

    void FireBullet() {
        float mouseX = Input.GetMouseX();
        float mouseY = Input.GetMouseY();
        Vector2 mousePosition = Vector2(mouseX, mouseY);

        Vector2 playerPosition = transform->position;

        Vector2 direction = mousePosition - playerPosition;
        direction.Normalize();

        float halfCannonSizeY = cannon->GetSize().y * 0.5f;

        Vector2 edgePosition = CalculateEdgePosition(playerPosition, direction, halfCannonSizeY);

        float bulletSpeed = 8000.0f;
        Vector2 bulletVelocity = direction * bulletSpeed;

        float angleRadians = atan2(direction.y, direction.x);
        float angleDegrees = angleRadians * (180.0f / M_PI);
        angleDegrees -= 90.0f;

        Bullet* bullet = new Bullet(edgePosition, bulletVelocity, 1);

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

    void Render() override {
        Player::Render();
        cannon->Render();
    }

    void OnCollisionEnter(Object* other) override {
        if (Enemy* enemy = dynamic_cast<Enemy*>(other)) {
            float currentTime = TIME.GetElapsedTime();

            //2 segons de cooldown
            if (currentTime - lastDamageTime >= 2.0f) {

                lives--;
                lastDamageTime = currentTime;

                if (lives <= 0) {
                    Destroy();
                    cannon->Destroy();
                }
            }
        }
        if (Bullet* bullet = dynamic_cast<Bullet*>(other)) {
            if (!bullet->IsFriendly()) {

                Destroy();
                other->Destroy();
            }
        }
    }
};