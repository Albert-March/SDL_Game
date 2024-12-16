#pragma once
#include "../ImageObject.h"
#include "../TimeManager.h"
#include "../InputManager.h"
#include "../Enemies/Enemy.h"

class Player : public ImageObject {
protected:
    int lives = 3;
    float lastDamageTime;

public:
    Player(std::string imagePath, Vector2 position, Vector2 size)
        : ImageObject(imagePath, Vector2(0.f, 0.f), size) {
        transform->position = position;
        transform->rotation = 0.0f;
        transform->scale = Vector2(1.f, 1.f);
    }

    virtual void Update() override {
        ImageObject::Update();
    }
    virtual void Render() override {
        ImageObject::Render();
    }
    virtual void Movement() = 0;
};