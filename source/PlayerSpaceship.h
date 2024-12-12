#pragma once
#include "ImageObject.h"
#include "RenderManager.h"
#include "TimeManager.h"
#include "Bullet.h"

class PlayerSpaceship : public ImageObject {
public:

	PlayerSpaceship(Vector2 pos)
		: ImageObject("resources/cat.jpg", Vector2(0.f, 0.f), Vector2(1500.f, 1500.f)) {
		transform->position = pos;
		transform->rotation = 0.0f;
		transform->scale = Vector2(1.f, 1.f);
	}

    void Update() override {
        Movement();
        Shooting();
        ImageObject::Update();
    }

    void Movement() {
        float speed = 10.0f;
        if (RM->IsKeyPressed(SDL_SCANCODE_LEFT)) {
            transform->position.x -= speed;
        }
        if (RM->IsKeyPressed(SDL_SCANCODE_RIGHT)) {
            transform->position.x += speed;
        }

        float halfWidth = transform->size.x * 0.5f * transform->scale.x;
        if (transform->position.x - halfWidth < 0) {
            transform->position.x = halfWidth;
        }
        if (transform->position.x + halfWidth > RM->WINDOW_WIDTH) {
            transform->position.x = RM->WINDOW_WIDTH - halfWidth;
        }
    }

    float lastShotTime = 0.0f;
    const float shootCooldown = 1.0f;
    bool spaceHeld = false;

    void Shooting() {
        float currentTime = TIME.GetElapsedTime();

        if (RM->IsKeyPressed(SDL_SCANCODE_SPACE)) {
            if (!spaceHeld) {
                FireBullet();
                lastShotTime = currentTime;
                spaceHeld = true;
            }
            else if (currentTime - lastShotTime >= shootCooldown) {
                FireBullet();
                lastShotTime = currentTime;
            }
        }
        else {
            spaceHeld = false;
        }
    }

    void FireBullet() {
        float halfPlayerHeight = transform->size.y * 0.5f * transform->scale.y;
        float halfBulletHeight = 50.0f;
        float bulletYPosition = transform->position.y - halfPlayerHeight - halfBulletHeight;

        Vector2 bulletPosition = Vector2(transform->position.x, bulletYPosition);
        Vector2 bulletVelocity = Vector2(0, -8000.0f);

        Bullet* bullet = new Bullet(bulletPosition, bulletVelocity);
        SPAWN.SpawnObject(bullet);

        std::cout << "Bullet fired!" << std::endl;
    }

    void Render() override {
        ImageObject::Render();
    }

    void OnCollisionEnter(Object* other) override {
        Destroy();
    }
};