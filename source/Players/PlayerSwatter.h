#pragma once
#include "Player.h"
#include "../ImageObject.h"
#include "../TimeManager.h"
#include "../InputManager.h"
#include "../Rigidbody.h"

class PlayerSwatter : public Player {
public:

	bool isColliding;
	bool isPaused = false;
	float pauseStartTime = 0.0f;

	PlayerSwatter(Vector2 pos)
		: Player("resources/Swatter.png", pos, Vector2(1500.f, 1500.f)) {
	}

	void Update() override {
		if (Input.GetLeftClick()) {
			
		}
		if (isPaused) {
			HandlePause();
		}
		else {
			Movement();
		}
		Player::Update();
	}

	void HandlePause() {
		float currentTime = TIME.GetElapsedTime();
		if (currentTime - pauseStartTime >= 2.0f) {
			isPaused = false;
		}
	}

	void StartPause() {
		isPaused = true;
		pauseStartTime = TIME.GetElapsedTime();
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
		if (Input.GetLeftClick()) {
			
			if (Enemy* to = reinterpret_cast<Enemy*>(other)) {
				//Destroy();
				other->Destroy();
				StartPause();
			}
		}
	}

	void Render() override {
		Player::Render();
	}
};