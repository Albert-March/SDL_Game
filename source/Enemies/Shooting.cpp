#include "Shooting.h"
#include "../Spawner.h"


void Shooting::Update()
{
    Movement();
    Shoot();
    Enemy::Update();
}

void Shooting::Movement()
{
	Enemy::Movement();
}

void Shooting::OnCollisionEnter(Object* other)
{
	//if (Bullet* to = reinterpret_cast<Bullet*>(other)) {
	//	Destroy();
	//	other->Destroy();
 //       CleanUp();
	//}
}

void Shooting::Render()
{
	Enemy::Render();
}

void Shooting::Shoot()
{
    static float lastShotTime = 0; 
    const float shotInterval = 1.0f; 

    float currentTime = TIME.GetElapsedTime();

    if (currentTime - lastShotTime >= shotInterval) {
        float rotationRadians = transform->rotation * 3.14159265f / 180.0f;

        Vector2 direction(cos(rotationRadians), sin(rotationRadians));
        direction.Normalize(); 


        float bulletSpeed = 8000.0f;
        Vector2 bulletVelocity = direction * bulletSpeed;

        float angleRadians = atan2(direction.y, direction.x);
        float angleDegrees = angleRadians * (180.0f / M_PI);
        angleDegrees -= 90.0f;

        Bullet* bullet = new Bullet(transform->position, bulletVelocity);

        bullet->SetRotation(transform->rotation);

        bullets.push_back(bullet);

        lastShotTime = currentTime;

        SPAWN.SpawnObject(bullet);
    }
}

void Shooting::CleanUp() {
    for (Bullet* bullet : bullets) {
        delete bullet; 
    }
    bullets.clear();
}
