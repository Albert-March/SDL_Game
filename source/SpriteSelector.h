#pragma once
#include "Scene.h"
#include "TextObject.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "AudioManager.h"

class SpriteSelector : public Scene
{
private:
    TextObject* TextSelectorSprites;

    TextObject* backgroundButton;
    ImageObject* background_1;
    ImageObject* background_2;
    ImageObject* background_3;

    TextObject* enemies;
    ImageObject* enemies_1;
    ImageObject* enemies_2;
    ImageObject* enemies_3;

    TextObject* VFX;
    ImageObject* VFX_1;
    ImageObject* VFX_2;
    ImageObject* VFX_3;

    ImageObject* selectedBackground;
    static Vector2 selectedBackgroundPos;

    ImageObject* selectedEnemies;
    static Vector2 selectedEnemiesPos;

    ImageObject* selectedVFX;
    static Vector2 selectedVFXPos;

    TextObject* buttonBack;

    static std::string backgroundSelected;
    static std::string enemySelected;
    static std::string VFXSelected;

    static int VFXframeWidth;
    static int VFXframeHeight;
    static int VFXNumRows;
    static int VFXNumColumns;

    SDL_Color normalColor = { 255, 255, 255, 255 };
    SDL_Color selectedColor = { 255, 0, 0, 255 };

    bool isLeftClick = false;
    bool pendingToChange = false;

    bool Collidingbackground_1 = false;
    bool Collidingbackground_2 = false;
    bool Collidingbackground_3 = false;

    bool Collidingenemies_1 = false;
    bool Collidingenemies_2 = false;
    bool Collidingenemies_3 = false;

    bool CollidingVFX_1 = false;
    bool CollidingVFX_2 = false;
    bool CollidingVFX_3 = false;

    bool buttonBackColliding = false;

public:
    SpriteSelector() = default;

    void OnEnter() override {

        TextSelectorSprites = new TextObject("Sprite Selector");
        TextSelectorSprites->GetTransform()->scale = Vector2(2.f, 2.f);
        TextSelectorSprites->GetTransform()->position = Vector2(RM->WINDOW_WIDTH / 2, 150);
        SPAWN.SpawnObject(TextSelectorSprites);


        backgroundButton = new TextObject("Background");
        backgroundButton->SetColor(normalColor);
        backgroundButton->GetTransform()->scale = Vector2(1.f, 1.f);
        backgroundButton->GetTransform()->position = Vector2(200, 300);
        SPAWN.SpawnObject(backgroundButton);

        selectedBackground = new ImageObject("resources/selected.png", Vector2(0.f, 0.f), Vector2(1360.f, 768.f));
        selectedBackground->GetTransform()->position = selectedBackgroundPos;
        selectedBackground->GetTransform()->scale = Vector2(1.2f, 1.2f);
        SPAWN.SpawnObject(selectedBackground);

        background_1 = new ImageObject("resources/Backgrounds/background_1.jpg", Vector2(0.f, 0.f), Vector2(1360.f, 768.f));
        background_1->GetTransform()->position = Vector2(430, 260);
        background_1->GetTransform()->scale = Vector2(1.f, 1.f);
        SPAWN.SpawnObject(background_1);

        background_2 = new ImageObject("resources/Backgrounds/background_2.jpg", Vector2(0.f, 0.f), Vector2(1360.f, 768.f));
        background_2->GetTransform()->position = Vector2(680, 260);
        background_2->GetTransform()->scale = Vector2(1.f, 1.f);
        SPAWN.SpawnObject(background_2);

        background_3 = new ImageObject("resources/Backgrounds/background_3.jpg", Vector2(0.f, 0.f), Vector2(1360.f, 768.f));
        background_3->GetTransform()->position = Vector2(930, 260);
        background_3->GetTransform()->scale = Vector2(1.f, 1.f);
        SPAWN.SpawnObject(background_3);

        //------------------------------------------------------------------------------------------------------------//

        enemies = new TextObject("Enemies ");
        enemies->SetColor(normalColor);
        enemies->GetTransform()->scale = Vector2(1.f, 1.f);
        enemies->GetTransform()->position = Vector2(200, 450);
        SPAWN.SpawnObject(enemies);

        selectedEnemies = new ImageObject("resources/selected.png", Vector2(0.f, 0.f), Vector2(1360.f, 768.f));
        selectedEnemies->GetTransform()->position = selectedEnemiesPos;
        selectedEnemies->GetTransform()->scale = Vector2(1.2f, 1.2f);
        SPAWN.SpawnObject(selectedEnemies);

        enemies_1 = new ImageObject("resources/Enemies/enemy_1.png", Vector2(0.f, 0.f), Vector2(1360.f, 768.f));
        enemies_1->GetTransform()->position = Vector2(430, 410);
        enemies_1->GetTransform()->scale = Vector2(1.f, 1.f);
        SPAWN.SpawnObject(enemies_1);

        enemies_2 = new ImageObject("resources/Enemies/enemy_2.png", Vector2(0.f, 0.f), Vector2(1360.f, 768.f));
        enemies_2->GetTransform()->position = Vector2(680, 410);
        enemies_2->GetTransform()->scale = Vector2(1.f, 1.f);
        SPAWN.SpawnObject(enemies_2);

        enemies_3 = new ImageObject("resources/Enemies/enemy_3.png", Vector2(0.f, 0.f), Vector2(1360.f, 768.f));
        enemies_3->GetTransform()->position = Vector2(930, 410);
        enemies_3->GetTransform()->scale = Vector2(1.f, 1.f);
        SPAWN.SpawnObject(enemies_3);

        //----------------------------------------------------------------------------------------------------------//

        VFX = new TextObject("VFX");
        VFX->SetColor(normalColor);
        VFX->GetTransform()->scale = Vector2(1.f, 1.f);
        VFX->GetTransform()->position = Vector2(200, 600);
        SPAWN.SpawnObject(VFX);

        selectedVFX = new ImageObject("resources/selected.png", Vector2(0.f, 0.f), Vector2(1360.f, 768.f));
        selectedVFX->GetTransform()->position = selectedVFXPos;
        selectedVFX->GetTransform()->scale = Vector2(1.2f, 1.2f);
        SPAWN.SpawnObject(selectedVFX);

        VFX_1 = new ImageObject("resources/VFX/VFX_1.png", Vector2(0.f, 0.f), Vector2(1360.f, 768.f));
        VFX_1->GetTransform()->position = Vector2(430, 560);
        VFX_1->GetTransform()->scale = Vector2(1.f, 1.f);
        SPAWN.SpawnObject(VFX_1);

        VFX_2 = new ImageObject("resources/VFX/VFX_2.png", Vector2(0.f, 0.f), Vector2(1360.f, 768.f));
        VFX_2->GetTransform()->position = Vector2(680, 560);
        VFX_2->GetTransform()->scale = Vector2(1.f, 1.f);
        SPAWN.SpawnObject(VFX_2);

        VFX_3 = new ImageObject("resources/VFX/VFX_3.png", Vector2(0.f, 0.f), Vector2(1360.f, 768.f));
        VFX_3->GetTransform()->position = Vector2(930, 560);
        VFX_3->GetTransform()->scale = Vector2(1.f, 1.f);
        SPAWN.SpawnObject(VFX_3);



        buttonBack = new TextObject("Back");
        buttonBack->SetColor(normalColor);
        buttonBack->GetTransform()->scale = Vector2(1.f, 1.f);
        buttonBack->GetTransform()->position = Vector2(RM->WINDOW_WIDTH / 2, 700);
        SPAWN.SpawnObject(buttonBack);
    }

    bool IsMouseOverSprite(ImageObject* button, Vector2 mousePos) {
        button->Update();

        float buttonW = button->GetTransform()->size.x * button->GetTransform()->scale.x;
        float buttonH = button->GetTransform()->size.y * button->GetTransform()->scale.y;
        float buttonX = button->GetTransform()->position.x - (buttonW / 2);
        float buttonY = button->GetTransform()->position.y - (buttonH / 2);


        return (mousePos.x >= buttonX && mousePos.x <= buttonX + buttonW &&
            mousePos.y >= buttonY && mousePos.y <= buttonY + buttonH);
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
        isLeftClick = Input.GetHoldClick();

        if (!IsMouseOverSprite(background_1, mousePos) &&
            !IsMouseOverSprite(background_2, mousePos) &&
            !IsMouseOverSprite(background_3, mousePos) &&
            !IsMouseOverSprite(enemies_1, mousePos) &&
            !IsMouseOverSprite(enemies_2, mousePos) &&
            !IsMouseOverSprite(enemies_3, mousePos) &&
            !IsMouseOverSprite(VFX_1, mousePos) &&
            !IsMouseOverSprite(VFX_2, mousePos) &&
            !IsMouseOverSprite(VFX_3, mousePos) &&
            !IsMouseOverButton(buttonBack, mousePos)) {
            pendingToChange = false;
        }

        //-------------------- BACKGROUND SELECTION -------------------------//
        if (IsMouseOverSprite(background_1, mousePos)) {
            background_1->GetTransform()->scale = Vector2(1.2f, 1.2f);
            if (selectedBackground->GetTransform()->position == background_1->GetTransform()->position)
                selectedBackground->GetTransform()->scale = Vector2(1.4f, 1.4f);
            if (isLeftClick) {
                pendingToChange = true;
            }
            if (!Collidingbackground_1) {
                AM.PlayClip("SelectButton", 0);
                Collidingbackground_1 = true;
            }
            if (!isLeftClick && pendingToChange) {
                backgroundSelected = "background_1.jpg";
                AM.PlayClip("ClickButton", 0);
                selectedBackgroundPos = Vector2(430, 260);
                selectedBackground->GetTransform()->position = selectedBackgroundPos;
                selectedBackground->GetTransform()->scale = Vector2(1.2f, 1.2f);
                pendingToChange = false;
            }
        }
        else {
            background_1->GetTransform()->scale = Vector2(1.0f, 1.0f);
            selectedBackground->GetTransform()->scale = Vector2(1.2f, 1.2f);
            Collidingbackground_1 = false;
        }

        if (IsMouseOverSprite(background_2, mousePos)) {
            background_2->GetTransform()->scale = Vector2(1.2f, 1.2f);
            if (selectedBackground->GetTransform()->position == background_2->GetTransform()->position)
                selectedBackground->GetTransform()->scale = Vector2(1.4f, 1.4f);
            if (isLeftClick) {
                pendingToChange = true;
            }
            if (!Collidingbackground_2) {
                AM.PlayClip("SelectButton", 0);
                Collidingbackground_2 = true;
            }
            if (!isLeftClick && pendingToChange) {
                backgroundSelected = "background_2.jpg";
                AM.PlayClip("ClickButton", 0);
                selectedBackgroundPos = Vector2(680, 260);
                selectedBackground->GetTransform()->position = selectedBackgroundPos;
                selectedBackground->GetTransform()->scale = Vector2(1.2f, 1.2f);
                pendingToChange = false;
            }
        }
        else {
            background_2->GetTransform()->scale = Vector2(1.0f, 1.0f);
            Collidingbackground_2 = false;
        }

        if (IsMouseOverSprite(background_3, mousePos)) {
            background_3->GetTransform()->scale = Vector2(1.2f, 1.2f);
            if (selectedBackground->GetTransform()->position == background_3->GetTransform()->position)
                selectedBackground->GetTransform()->scale = Vector2(1.4f, 1.4f);
            if (isLeftClick) {
                pendingToChange = true;
            }
            if (!Collidingbackground_3) {
                AM.PlayClip("SelectButton", 0);
                Collidingbackground_3 = true;
            }
            if (!isLeftClick && pendingToChange) {
                backgroundSelected = "background_3.jpg";
                AM.PlayClip("ClickButton", 0);
                selectedBackgroundPos = Vector2(930, 260);
                selectedBackground->GetTransform()->position = selectedBackgroundPos;
                selectedBackground->GetTransform()->scale = Vector2(1.2f, 1.2f);
                pendingToChange = false;
            }
        }
        else {
            background_3->GetTransform()->scale = Vector2(1.0f, 1.0f);
            Collidingbackground_3 = false;
        }

        //-------------------- ENEMIES SELECTION -----------------------//
        if (IsMouseOverSprite(enemies_1, mousePos)) {
            enemies_1->GetTransform()->scale = Vector2(1.2f, 1.2f);
            if (selectedEnemies->GetTransform()->position == enemies_1->GetTransform()->position)
                selectedEnemies->GetTransform()->scale = Vector2(1.4f, 1.4f);
            if (isLeftClick) {
                pendingToChange = true;
            }
            if (!Collidingenemies_1) {
                AM.PlayClip("SelectButton", 0);
                Collidingenemies_1 = true;
            }
            if (!isLeftClick && pendingToChange) {
                enemySelected = "enemy_1.png";
                AM.PlayClip("ClickButton", 0);
                selectedEnemiesPos = Vector2(430, 410);
                selectedEnemies->GetTransform()->position = selectedEnemiesPos;
                selectedEnemies->GetTransform()->scale = Vector2(1.2f, 1.2f);
                pendingToChange = false;
            }
        }
        else {
            enemies_1->GetTransform()->scale = Vector2(1.0f, 1.0f);
            selectedEnemies->GetTransform()->scale = Vector2(1.2f, 1.2f);
            Collidingenemies_1 = false;
        }

        if (IsMouseOverSprite(enemies_2, mousePos)) {
            enemies_2->GetTransform()->scale = Vector2(1.2f, 1.2f);
            if (selectedEnemies->GetTransform()->position == enemies_2->GetTransform()->position)
                selectedEnemies->GetTransform()->scale = Vector2(1.4f, 1.4f);
            if (isLeftClick) {
                pendingToChange = true;
            }
            if (!Collidingenemies_2) {
                AM.PlayClip("SelectButton", 0);
                Collidingenemies_2 = true;
            }
            if (!isLeftClick && pendingToChange) {
                enemySelected = "enemy_2.png";
                AM.PlayClip("ClickButton", 0);
                selectedEnemiesPos = Vector2(680, 410);
                selectedEnemies->GetTransform()->position = selectedEnemiesPos;
                selectedEnemies->GetTransform()->scale = Vector2(1.2f, 1.2f);
                pendingToChange = false;
            }
        }
        else {
            enemies_2->GetTransform()->scale = Vector2(1.0f, 1.0f);
            Collidingenemies_2 = false;
        }

        if (IsMouseOverSprite(enemies_3, mousePos)) {
            enemies_3->GetTransform()->scale = Vector2(1.2f, 1.2f);
            if (selectedEnemies->GetTransform()->position == enemies_3->GetTransform()->position)
                selectedEnemies->GetTransform()->scale = Vector2(1.4f, 1.4f);
            if (isLeftClick) {
                pendingToChange = true;
            }
            if (!Collidingenemies_3) {
                AM.PlayClip("SelectButton", 0);
                Collidingenemies_3 = true;
            }
            if (!isLeftClick && pendingToChange) {
                enemySelected = "enemy_3.png";
                AM.PlayClip("ClickButton", 0);
                selectedEnemiesPos = Vector2(930, 410);
                selectedEnemies->GetTransform()->position = selectedEnemiesPos;
                selectedEnemies->GetTransform()->scale = Vector2(1.2f, 1.2f);
                pendingToChange = false;
            }
        }
        else {
            enemies_3->GetTransform()->scale = Vector2(1.0f, 1.0f);
            Collidingenemies_3 = false;
        }

        //-------------------- VFX -----------------------//
        if (IsMouseOverSprite(VFX_1, mousePos)) {
            VFX_1->GetTransform()->scale = Vector2(1.2f, 1.2f);
            if (selectedVFX->GetTransform()->position == VFX_1->GetTransform()->position)
                selectedVFX->GetTransform()->scale = Vector2(1.4f, 1.4f);
            if (isLeftClick) {
                pendingToChange = true;
            }
            if (!CollidingVFX_1) {
                AM.PlayClip("SelectButton", 0);
                CollidingVFX_1 = true;
            }
            if (!isLeftClick && pendingToChange) {
                VFXSelected = "VFX_1.png";
                VFXframeWidth = 626;
                VFXframeHeight = 313;
                VFXNumRows = 4;
                VFXNumColumns = 2;
                AM.PlayClip("ClickButton", 0);
                selectedVFXPos = Vector2(430, 560);
                selectedVFX->GetTransform()->position = selectedVFXPos;
                selectedVFX->GetTransform()->scale = Vector2(1.2f, 1.2f);
                pendingToChange = false;
            }
        }
        else {
            VFX_1->GetTransform()->scale = Vector2(1.0f, 1.0f);
            selectedVFX->GetTransform()->scale = Vector2(1.2f, 1.2f);
            CollidingVFX_1 = false;
        }

        if (IsMouseOverSprite(VFX_2, mousePos)) {
            VFX_2->GetTransform()->scale = Vector2(1.2f, 1.2f);
            if (selectedVFX->GetTransform()->position == VFX_2->GetTransform()->position)
                selectedVFX->GetTransform()->scale = Vector2(1.4f, 1.4f);
            if (isLeftClick) {
                pendingToChange = true;
            }
            if (!CollidingVFX_2) {
                AM.PlayClip("SelectButton", 0);
                CollidingVFX_2 = true;
            }
            if (!isLeftClick && pendingToChange) {
                VFXSelected = "VFX_2.png";
                VFXframeWidth = 1920;
                VFXframeHeight = 960;
                VFXNumRows = 5;
                VFXNumColumns = 2;
                AM.PlayClip("ClickButton", 0);
                selectedVFXPos = Vector2(680, 560);
                selectedVFX->GetTransform()->position = selectedVFXPos;
                selectedVFX->GetTransform()->scale = Vector2(1.2f, 1.2f);
                pendingToChange = false;
            }
        }
        else {
            VFX_2->GetTransform()->scale = Vector2(1.0f, 1.0f);
            CollidingVFX_2 = false;
        }

        if (IsMouseOverSprite(VFX_3, mousePos)) {
            VFX_3->GetTransform()->scale = Vector2(1.2f, 1.2f);
            if (selectedVFX->GetTransform()->position == VFX_3->GetTransform()->position)
                selectedVFX->GetTransform()->scale = Vector2(1.4f, 1.4f);
            if (isLeftClick) {
                pendingToChange = true;
            }
            if (!CollidingVFX_3) {
                AM.PlayClip("SelectButton", 0);
                CollidingVFX_3 = true;
            }
            if (!isLeftClick && pendingToChange) {
                VFXSelected = "VFX_3.png";
                VFXframeWidth = 1920;
                VFXframeHeight = 384;
                VFXNumRows = 7;
                VFXNumColumns = 1;
                AM.PlayClip("ClickButton", 0);
                selectedVFXPos = Vector2(930, 560);
                selectedVFX->GetTransform()->position = selectedVFXPos;
                selectedVFX->GetTransform()->scale = Vector2(1.2f, 1.2f);
                pendingToChange = false;
            }
        }
        else {
            VFX_3->GetTransform()->scale = Vector2(1.0f, 1.0f);
            CollidingVFX_3 = false;
        }

        // ---------------------- BOTÓN BACK ---------------------------//
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

    ~SpriteSelector() {
        delete backgroundButton;
        delete enemies;
        delete VFX;
    }

    static std::string GetSelectedBackground() { return backgroundSelected; }
    static std::string GetSelectedEnemy() { return enemySelected; }
    static std::string GetSelectedVFX() { return VFXSelected; }

    static int GetVFXNumRows() { return VFXNumRows; }
    static int GetVFXNumColumns() { return VFXNumColumns; }
    static int GetVFXframeWidth() { return VFXframeWidth; }
    static int GetVFXframeHeight() { return VFXframeHeight; }

};
std::string SpriteSelector::backgroundSelected = "background_1.jpg";
std::string SpriteSelector::enemySelected = "enemy_1.png";
std::string SpriteSelector::VFXSelected = "VFX_1.png";

int SpriteSelector::VFXframeWidth = 626;
int SpriteSelector::VFXframeHeight = 313;
int SpriteSelector::VFXNumRows = 4;
int SpriteSelector::VFXNumColumns = 2;

Vector2 SpriteSelector::selectedBackgroundPos = Vector2(430, 260);
Vector2 SpriteSelector::selectedEnemiesPos = Vector2(430, 410);
Vector2 SpriteSelector::selectedVFXPos = Vector2(430, 560);