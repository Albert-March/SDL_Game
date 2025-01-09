#pragma once
#include "Scene.h"
#include "TextObject.h"
#include "InputManager.h"
#include "SceneManager.h"

class PlayMenu : public Scene
{
private:
    TextObject* buttonTanks;
    TextObject* buttonSwatter;
    TextObject* buttonSpaceInvaders;
    TextObject* buttonBack;

    bool buttonTanksColliding = false;
    bool buttonSwatterColliding = false;
    bool buttonSpaceInvadersColliding = false;
    bool buttonBackColliding = false;

    int selectedOption;

    SDL_Color normalColor = { 255, 255, 255, 255 };
    SDL_Color selectedColor = { 255, 0, 0, 255 };

    bool isLeftClick = false;
    bool pendingToChange = false;

public:
    PlayMenu() = default;

    void OnEnter() override {
        selectedOption = 0;

        buttonSpaceInvaders = new TextObject("Space Invaders Game");
        buttonSpaceInvaders->SetColor(normalColor);
        buttonSpaceInvaders->GetTransform()->scale = Vector2(1.5f, 1.5f);
        buttonSpaceInvaders->GetTransform()->position = Vector2(RM->WINDOW_WIDTH / 2, 250);
        SPAWN.SpawnObject(buttonSpaceInvaders);

        buttonTanks = new TextObject("Tanks Game");
        buttonTanks->SetColor(selectedColor);
        buttonTanks->GetTransform()->scale = Vector2(1.5f, 1.5f);
        buttonTanks->GetTransform()->position = Vector2(RM->WINDOW_WIDTH / 2, 400);
        SPAWN.SpawnObject(buttonTanks);

        buttonSwatter = new TextObject("Swatter Game");
        buttonSwatter->SetColor(normalColor);
        buttonSwatter->GetTransform()->scale = Vector2(1.5f, 1.5f);
        buttonSwatter->GetTransform()->position = Vector2(RM->WINDOW_WIDTH / 2, 550);
        SPAWN.SpawnObject(buttonSwatter);


        buttonBack = new TextObject("Back");
        buttonBack->SetColor(normalColor);
        buttonBack->GetTransform()->scale = Vector2(1.5f, 1.5f);
        buttonBack->GetTransform()->position = Vector2(RM->WINDOW_WIDTH / 2, 700);
        SPAWN.SpawnObject(buttonBack);
    }

    bool IsMouseOverButton(TextObject* button, Vector2 mousePos) {
        button->Update();

        SDL_Rect destRect = button->GetDestRect();
        float buttonX = destRect.x;
        float buttonY = destRect.y;
        float buttonW = destRect.w;
        float buttonH = destRect.h;

        return (mousePos.x >= buttonX && mousePos.x <= buttonX + buttonW &&
            mousePos.y >= buttonY && mousePos.y <= buttonY + buttonH);
    }

    void Update() override {
        Vector2 mousePos = Vector2(Input.GetMouseX(), Input.GetMouseY());
        isLeftClick = Input.GetLeftClick();

        if (!IsMouseOverButton(buttonTanks, mousePos) && !IsMouseOverButton(buttonSwatter, mousePos) && !IsMouseOverButton(buttonSpaceInvaders, mousePos) && !IsMouseOverButton(buttonBack, mousePos))
            pendingToChange = false;


        if (IsMouseOverButton(buttonSpaceInvaders, mousePos)) {
            buttonSpaceInvaders->SetColor(selectedColor);
            if (isLeftClick) {
                pendingToChange = true;
            }
            if (!buttonSpaceInvadersColliding) {
                AM.PlayClip("SelectButton", 0);
                buttonSpaceInvadersColliding = true;
            }
            if (!isLeftClick && pendingToChange) {
                SM.SetNextScene("SpaceInvaders");
                AM.PlayClip("ClickButton", 0);
                pendingToChange = false;
            }
        }
        else {
            buttonSpaceInvaders->SetColor(normalColor);
            buttonSpaceInvadersColliding = false;
        }

        if (IsMouseOverButton(buttonTanks, mousePos)) {
            buttonTanks->SetColor(selectedColor);
            if (isLeftClick) {
                pendingToChange = true;
            }
            if (!buttonTanksColliding) {
                AM.PlayClip("SelectButton", 0);
                buttonTanksColliding = true;
            }
            if (!isLeftClick && pendingToChange) {
                SM.SetNextScene("Tanks");
                AM.PlayClip("ClickButton", 0);
                pendingToChange = false;
            }
        }
        else {
            buttonTanks->SetColor(normalColor);
            buttonTanksColliding = false;
        }

        if (IsMouseOverButton(buttonSwatter, mousePos)) {
            buttonSwatter->SetColor(selectedColor);
            if (isLeftClick) {
                pendingToChange = true;
            }
            if (!buttonSwatterColliding) {
                AM.PlayClip("SelectButton", 0);
                buttonSwatterColliding = true;
            }
            if (!isLeftClick && pendingToChange) {
                SM.SetNextScene("Swatter");
                AM.PlayClip("ClickButton", 0);
                pendingToChange = false;
            }
        }
        else {
            buttonSwatter->SetColor(normalColor);
            buttonSwatterColliding = false;
        }


        if (IsMouseOverButton(buttonBack, mousePos)) {
            buttonBack->SetColor(selectedColor);
            if (isLeftClick) {
                pendingToChange = true;
            }
            if (!buttonBackColliding) {
                AM.PlayClip("SelectButton", 0);
                buttonBackColliding = true;
            }
            if (!isLeftClick && pendingToChange) {
                SM.SetNextScene("Main Menu");
                AM.PlayClip("ClickButton", 0);
                pendingToChange = false;
            }
        }
        else {
            buttonBack->SetColor(normalColor);
            buttonBackColliding = false;
        }

        Scene::Update();
    }

    void Render() override {
        Scene::Render();
    }

    ~PlayMenu() {
        delete buttonTanks;
        delete buttonSwatter;
        delete buttonSpaceInvaders;
        delete buttonBack;
    }
};