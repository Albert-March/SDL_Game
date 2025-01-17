#pragma once
#include "SceneManager.h"
#include "ImageObject.h"
#include "TextObject.h"
#include "InputManager.h"
#include "TimeManager.h"

class SplashScreen : public Scene {
private:
    ImageObject* background;
    ImageObject* loadingImage;
    float timer = 0.0f;
    const float duration = 3.0f;

public:
    SplashScreen() = default;

    void OnEnter() override {
        background = new ImageObject("resources/SplashScreen.png", Vector2(0.f, 0.f), Vector2(1366.f, 768.f));
        background->GetTransform()->position = Vector2(RM->WINDOW_WIDTH / 2, RM->WINDOW_HEIGHT / 2);
        background->GetTransform()->scale = Vector2(13.6f, 7.68f);
        SPAWN.SpawnObject(background);

        loadingImage = new ImageObject("resources/LoadingImage.png", Vector2(0.f, 0.f), Vector2(1366.f, 768.f));
        loadingImage->GetTransform()->position = Vector2(RM->WINDOW_WIDTH / 2, (RM->WINDOW_HEIGHT/2) + 50);
        loadingImage->GetTransform()->scale = Vector2(13.6f, 7.68f);
        SPAWN.SpawnObject(loadingImage);
    }

    void Update() override {
        timer += TIME.GetDeltaTime();

        if (static_cast<int>(timer * 2) % 2 == 0) {
            loadingImage->GetTransform()->position = Vector2(RM->WINDOW_WIDTH / 2, (RM->WINDOW_HEIGHT / 2) + 50);
        }
        else {
            loadingImage->GetTransform()->position = Vector2(-300.f, 0.f); //Perque no surti a la pantalla
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
        delete loadingImage;
    }
};
