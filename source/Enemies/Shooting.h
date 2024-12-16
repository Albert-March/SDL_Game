#pragma once
#include "../Enemies/Enemy.h"
#include "../RenderManager.h"
#include "../Players/Player.h"
#include "../Bullet.h"

class Shooting : public Enemy {

public:
	Shooting(Vector2 pos, Player* player)
		: Enemy("resources/PS_Enemy.png", pos, Vector2(1500.f, 1500.f)) {
	}

	void Update() override;

	void Movement() override;

	void OnCollisionEnter(Object* other) override;

	void Render() override;

	void Shoot();

	void CleanUp();

private: 
	std::vector<Bullet*> bullets;
};