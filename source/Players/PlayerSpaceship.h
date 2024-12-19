#pragma once
#include "Player.h"
#include "../ImageObject.h"
#include "../RenderManager.h"
#include "../TimeManager.h"
#include "../Players/Bullet.h"
#include "../InputManager.h"
#include "../SceneManager.h"

class PlayerSpaceship : public Player {
public:

	PlayerSpaceship(Vector2 pos)
		: Player("resources/Spaceship.png", Vector2(0.f, 0.f), Vector2(256.f, 256.f)) {
		transform->position = pos;
		transform->rotation = 0.0f;
		transform->scale = Vector2(1.f, 1.f);
	}

    void Update() override {
        Movement();
        Shooting();
        Player::Update();
    }

    void Movement() override {
        float speed = 10.0f;
        if (Input.GetEvent(SDLK_LEFT, HOLD) || Input.GetEvent(SDLK_a, HOLD)) {
            transform->position.x -= speed;
        }
        if (Input.GetEvent(SDLK_RIGHT, HOLD) || Input.GetEvent(SDLK_d, HOLD)) {
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

    void FireBullet() {
        float halfPlayerHeight = transform->size.y * 0.5f * transform->scale.y;

        float bulletYPosition = transform->position.y - halfPlayerHeight;

        Vector2 bulletPosition = Vector2(transform->position.x, bulletYPosition);
        Vector2 bulletVelocity = Vector2(0, -8000.0f);

        Bullet* bullet = new Bullet(bulletPosition, bulletVelocity, 1);
        SPAWN.SpawnObject(bullet);

        std::cout << "Bullet fired!" << std::endl;
    }

    void Render() override {
        Player::Render();
    }

    void OnCollisionEnter(Object* other) override {
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
            SM.SetNextScene("SpaceInvaders");
            lives = 3; //Torna a comensar
        }
    }
};