#pragma once
#include "../ImageObject.h"
#include "../TimeManager.h"
#include "../InputManager.h"

class Enemy : public ImageObject {

public:
    Enemy(std::string imagePath, Vector2 position, Vector2 size)
        : ImageObject(imagePath, Vector2(0.f, 0.f), size) {
        transform->position = position;
        transform->rotation = 0.0f;
        transform->scale = Vector2(0.5f, 0.5f);
        GenerateRandomPattern(8);
    }

    virtual void Update() override {
        ImageObject::Update();
    }
    virtual void Render() override {
        ImageObject::Render();
    }
protected:
    virtual void Movement() {
        static size_t currentStep = 0;
        static float phaseStartTime = 0;
        static const float moveDuration = 1.0f;
        static const float waitDuration = 0.5f;

        float currentTime = TIME.GetElapsedTime();

        if (currentTime - phaseStartTime < moveDuration) {
            Vector2 direction = pattern[currentStep];
            direction.Normalize();

            float speed = 100.0f * TIME.GetDeltaTime();

            transform->position = transform->position + direction * speed;

            KeepInsideWindow();
        }
        else {
            phaseStartTime = currentTime;
            currentStep = (currentStep + 1) % pattern.size();
        }
    }

private:
    std::vector<Vector2> pattern;

    void GenerateRandomPattern(size_t steps) {
        pattern.clear();

        for (size_t i = 0; i < steps; ++i) {
            int direction = rand() % 8 + 1;
            switch (direction) {
            case 1: pattern.emplace_back(0, -1); break;
            case 2: pattern.emplace_back(0, 1); break;
            case 3: pattern.emplace_back(-1, 0); break;
            case 4: pattern.emplace_back(1, 0); break;
            case 5: pattern.emplace_back(-2.f, -2.f); break;
            case 6: pattern.emplace_back(2.f, -2.f); break;
            case 7: pattern.emplace_back(-2.f, 2.f); break;
            case 8: pattern.emplace_back(2.f, 2.f); break;
            }
        }
    }

    void KeepInsideWindow() {
        float halfWidth = transform->size.x * 0.5f * transform->scale.x;
        float halfHeight = transform->size.y * 0.5f * transform->scale.y;

        if (transform->position.x - halfWidth < 0) {
            transform->position.x = halfWidth;
        }
        if (transform->position.x + halfWidth > RM->WINDOW_WIDTH) {
            transform->position.x = RM->WINDOW_WIDTH - halfWidth;
        }
        if (transform->position.y - halfHeight < 0) {
            transform->position.y = halfHeight;
        }
        if (transform->position.y + halfHeight > RM->WINDOW_HEIGHT) {
            transform->position.y = RM->WINDOW_HEIGHT - halfHeight;
        }
    }
};