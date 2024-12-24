#pragma once
#include "SceneManager.h"
#include "ImageObject.h"
#include "TextObject.h"
#include "InputManager.h"
#include "TimeManager.h"

class SplashScreen : public Scene {
private:
    ImageObject* background;
    ImageObject* logo;
    TextObject* loadingText;
    float timer = 0.0f;
    const float duration = 3.0f;

public:
    SplashScreen() = default;

    void OnEnter() override {
        background = new ImageObject("resources/MenuBackground.jpg", Vector2(0.f, 0.f), Vector2(1366.f, 768.f));
        background->GetTransform()->position = Vector2(RM->WINDOW_WIDTH / 2, RM->WINDOW_HEIGHT / 2);
        background->GetTransform()->scale = Vector2(13.6f, 7.68f);
        SPAWN.SpawnObject(background);

        logo = new ImageObject("resources/MenuBackground.jpg", Vector2(0.f, 0.f), Vector2(500.f, 500.f));
        logo->GetTransform()->position = Vector2(RM->WINDOW_WIDTH / 2, RM->WINDOW_HEIGHT - 100);
        logo->GetTransform()->scale = Vector2(1.5f, 1.5f);
        SPAWN.SpawnObject(logo);

        loadingText = new TextObject("Loading...");
        loadingText->SetColor(SDL_Color{ 255, 255, 255, 255 });
        loadingText->GetTransform()->position = Vector2(RM->WINDOW_WIDTH / 2, RM->WINDOW_HEIGHT - 50);
        loadingText->GetTransform()->scale = Vector2(1.0f, 1.0f);
        SPAWN.SpawnObject(loadingText);
    }

    void Update() override {
        timer += TIME.GetDeltaTime();

        // Efecto de parpadeo en el texto
        if (static_cast<int>(timer * 2) % 2 == 0) {
            loadingText->SetColor(SDL_Color{ 255, 255, 255, 255 });
        }
        else {
            loadingText->SetColor(SDL_Color{ 200, 200, 200, 200 });
        }

        if (timer >= duration) {
            SM.SetNextScene("Main Menu");
        }

        Scene::Update();
    }

    void Render() override {
        Scene::Render();
    }

    ~SplashScreen() {
        delete background;
        delete logo;
        delete loadingText;
    }
};
