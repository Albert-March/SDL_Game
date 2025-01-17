#pragma once
#include "Scene.h"
#include "TextObject.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "AudioManager.h"

class Death : public Scene {
private:
    TextObject* deathText;
    std::string text;

    SDL_Color normalColor = { 255, 255, 255, 255 };
    SDL_Color selectedColor = { 255, 0, 0, 255 };

    int gameMode;
    int score;
    int lives;

    float timer = 0.0f;
    const float duration1 = 1.0f;
    const float duration2 = 2.0f;

    bool destroy = false;

public:
    Death() = default;

    void OnEnter() override {
        if (lives >= 1)
        {
            text = "You ar Death";
        }
        else {
            text = "Game Over";
        }
        deathText = new TextObject(text);
        std::cout << lives;
        std::cout << gameMode;
        deathText->SetColor(selectedColor);
        deathText->GetTransform()->scale = Vector2(3.f, 3.f);
        deathText->GetTransform()->position = Vector2(RM->WINDOW_WIDTH / 2, 300);
        SPAWN.SpawnObject(deathText);
    }


    bool IsMouseOverButton(TextObject* button, Vector2 mousePos) {
        button->Update();
        SDL_Rect destRect = button->GetDestRect();

        return (mousePos.x >= destRect.x && mousePos.x <= destRect.x + destRect.w &&
            mousePos.y >= destRect.y && mousePos.y <= destRect.y + destRect.h);
    }


    void Update() override {
        timer += TIME.GetDeltaTime();

        if (timer >= duration1 && destroy == false) {
            deathText->Destroy();    
            destroy = true;
        }
        if (timer >= (duration1 + duration2)) {
            timer = 0;
            if (gameMode == 0)
                SM.SetNextScene("SpaceInvaders");
            else if (gameMode == 1)
                SM.SetNextScene("Tanks");
            else if (gameMode == 2)
                SM.SetNextScene("Swatter");
        }

        Scene::Update();
    }

    void Render() override {
        Scene::Render();
    }

    ~Death() {
        SDL_StopTextInput();
        delete deathText;
    }

    void SetLivesAndMode(int newLives, int newGameMode) {
        lives = newLives;
        gameMode = newGameMode;
    }
};