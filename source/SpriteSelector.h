#pragma once
#pragma once
#include "Scene.h"
#include "TextObject.h"
#include "InputManager.h"
#include "SceneManager.h"

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

    ImageObject* disabledBackground;
    Vector2 disabledBackgroundPos = Vector2(650, 260);

    ImageObject* disabledEnemies;
    Vector2 disabledEnemiesPos = Vector2(650, 410);

    ImageObject* disabledVFX;
    Vector2 disabledVFXPos = Vector2(650, 560);

    TextObject* buttonBack;

    static std::string selectedBackground;
    static std::string selectedEnemy;
    static std::string selectedVFX;

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
        float halftext = TextSelectorSprites->GetSourceRect().w * TextSelectorSprites->GetTransform()->scale.x * 0.5f;
        TextSelectorSprites->GetTransform()->position = Vector2((RM->WINDOW_WIDTH / 2) - halftext, 150);
        SPAWN.SpawnObject(TextSelectorSprites);


        backgroundButton = new TextObject("Background");
        backgroundButton->SetColor(normalColor);
        backgroundButton->GetTransform()->scale = Vector2(1.f, 1.f);
        float halfbackground = backgroundButton->GetSourceRect().w * backgroundButton->GetTransform()->scale.x * 0.5f;
        backgroundButton->GetTransform()->position = Vector2(350 - halfbackground, 300);
        SPAWN.SpawnObject(backgroundButton);

        disabledBackground = new ImageObject("resources/Backgrounds/disabled.png", Vector2(0.f, 0.f), Vector2(1360.f, 768.f));
        disabledBackground->GetTransform()->position = disabledBackgroundPos;
        disabledBackground->GetTransform()->scale = Vector2(1.2f, 1.2f);
        SPAWN.SpawnObject(disabledBackground);

        background_1 = new ImageObject("resources/Backgrounds/background_1.jpg", Vector2(0.f, 0.f), Vector2(1360.f, 768.f));
        background_1->GetTransform()->position = Vector2(650, 260);
        background_1->GetTransform()->scale = Vector2(1.f, 1.f);
        SPAWN.SpawnObject(background_1);

        background_2 = new ImageObject("resources/Backgrounds/background_2.jpg", Vector2(0.f, 0.f), Vector2(1360.f, 768.f));
        background_2->GetTransform()->position = Vector2(900, 260);
        background_2->GetTransform()->scale = Vector2(1.f, 1.f);
        SPAWN.SpawnObject(background_2);

        background_3 = new ImageObject("resources/Backgrounds/background_3.jpg", Vector2(0.f, 0.f), Vector2(1360.f, 768.f));
        background_3->GetTransform()->position = Vector2(1150, 260);
        background_3->GetTransform()->scale = Vector2(1.f, 1.f);
        SPAWN.SpawnObject(background_3);

        //------------------------------------------------------------------------------------------------------------//

        enemies = new TextObject("Enemies ");
        enemies->SetColor(normalColor);
        enemies->GetTransform()->scale = Vector2(1.f, 1.f);
        float halfenemies = enemies->GetSourceRect().w * enemies->GetTransform()->scale.x * 0.5f;
        enemies->GetTransform()->position = Vector2(350 - halfenemies, 450);
        SPAWN.SpawnObject(enemies);

        disabledEnemies = new ImageObject("resources/Backgrounds/disabled.png", Vector2(0.f, 0.f), Vector2(1360.f, 768.f));
        disabledEnemies->GetTransform()->position = disabledEnemiesPos;
        disabledEnemies->GetTransform()->scale = Vector2(1.2f, 1.2f);
        SPAWN.SpawnObject(disabledEnemies);

        enemies_1 = new ImageObject("resources/MenuBackground.jpg", Vector2(0.f, 0.f), Vector2(1360.f, 768.f));
        enemies_1->GetTransform()->position = Vector2(650, 410);
        enemies_1->GetTransform()->scale = Vector2(1.f, 1.f);
        SPAWN.SpawnObject(enemies_1);

        enemies_2 = new ImageObject("resources/MenuBackground.jpg", Vector2(0.f, 0.f), Vector2(1360.f, 768.f));
        enemies_2->GetTransform()->position = Vector2(900, 410);
        enemies_2->GetTransform()->scale = Vector2(1.f, 1.f);
        SPAWN.SpawnObject(enemies_2);

        enemies_3 = new ImageObject("resources/MenuBackground.jpg", Vector2(0.f, 0.f), Vector2(1360.f, 768.f));
        enemies_3->GetTransform()->position = Vector2(1150, 410);
        enemies_3->GetTransform()->scale = Vector2(1.f, 1.f);
        SPAWN.SpawnObject(enemies_3);

        //----------------------------------------------------------------------------------------------------------//

        VFX = new TextObject("VFX");
        VFX->SetColor(normalColor);
        VFX->GetTransform()->scale = Vector2(1.f, 1.f);
        float halfVFX = VFX->GetSourceRect().w * VFX->GetTransform()->scale.x * 0.5f;
        VFX->GetTransform()->position = Vector2(350 - halfVFX, 600);
        SPAWN.SpawnObject(VFX);

        disabledVFX = new ImageObject("resources/Backgrounds/disabled.png", Vector2(0.f, 0.f), Vector2(1360.f, 768.f));
        disabledVFX->GetTransform()->position = disabledVFXPos;
        disabledVFX->GetTransform()->scale = Vector2(1.2f, 1.2f);
        SPAWN.SpawnObject(disabledVFX);

        VFX_1 = new ImageObject("resources/MenuBackground.jpg", Vector2(0.f, 0.f), Vector2(1360.f, 768.f));
        VFX_1->GetTransform()->position = Vector2(650, 560);
        VFX_1->GetTransform()->scale = Vector2(1.f, 1.f);
        SPAWN.SpawnObject(VFX_1);

        VFX_2 = new ImageObject("resources/MenuBackground.jpg", Vector2(0.f, 0.f), Vector2(1360.f, 768.f));
        VFX_2->GetTransform()->position = Vector2(900, 560);
        VFX_2->GetTransform()->scale = Vector2(1.f, 1.f);
        SPAWN.SpawnObject(VFX_2);

        VFX_3 = new ImageObject("resources/MenuBackground.jpg", Vector2(0.f, 0.f), Vector2(1360.f, 768.f));
        VFX_3->GetTransform()->position = Vector2(1150, 560);
        VFX_3->GetTransform()->scale = Vector2(1.f, 1.f);
        SPAWN.SpawnObject(VFX_3);



        buttonBack = new TextObject("Back");
        buttonBack->SetColor(normalColor);
        buttonBack->GetTransform()->scale = Vector2(1.f, 1.f);
        float halfButtonBack = buttonBack->GetSourceRect().w * buttonBack->GetTransform()->scale.x * 0.5f;
        buttonBack->GetTransform()->position = Vector2((RM->WINDOW_WIDTH / 2) - halfButtonBack, 750);
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
        isLeftClick = Input.GetLeftClick();

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
            if(disabledBackground->GetTransform()->position == background_1->GetTransform()->position)
                disabledBackground->GetTransform()->scale = Vector2(1.4f, 1.4f);
            if (isLeftClick) {
                pendingToChange = true;
            }
            if (!Collidingbackground_1) {
                AM.PlayClip("SelectButton", 0);
                Collidingbackground_1 = true;
            }
            if (!isLeftClick && pendingToChange) {
                selectedBackground = "background_1.jpg";
                AM.PlayClip("ClickButton", 0);
                disabledBackground->GetTransform()->position = Vector2(650, 260);
                disabledBackground->GetTransform()->scale = Vector2(1.2f, 1.2f);
                pendingToChange = false;
            }
        }
        else {
            background_1->GetTransform()->scale = Vector2(1.0f, 1.0f);
            disabledBackground->GetTransform()->scale = Vector2(1.2f, 1.2f);
            Collidingbackground_1 = false;
        }

        if (IsMouseOverSprite(background_2, mousePos)) {
            background_2->GetTransform()->scale = Vector2(1.2f, 1.2f);
            if (disabledBackground->GetTransform()->position == background_2->GetTransform()->position)
                disabledBackground->GetTransform()->scale = Vector2(1.4f, 1.4f);
            if (isLeftClick) {
                pendingToChange = true;
            }
            if (!Collidingbackground_2) {
                AM.PlayClip("SelectButton", 0);
                Collidingbackground_2 = true;
            }
            if (!isLeftClick && pendingToChange) {
                selectedBackground = "background_2.jpg";
                AM.PlayClip("ClickButton", 0);
                disabledBackground->GetTransform()->position = Vector2(900, 260);
                disabledBackground->GetTransform()->scale = Vector2(1.2f, 1.2f);
                pendingToChange = false;
            }
        }
        else {
            background_2->GetTransform()->scale = Vector2(1.0f, 1.0f);
            Collidingbackground_2 = false;
        }

        if (IsMouseOverSprite(background_3, mousePos)) {
            background_3->GetTransform()->scale = Vector2(1.2f, 1.2f);
            if (disabledBackground->GetTransform()->position == background_3->GetTransform()->position)
                disabledBackground->GetTransform()->scale = Vector2(1.4f, 1.4f);
            if (isLeftClick) {
                pendingToChange = true;
            }
            if (!Collidingbackground_3) {
                AM.PlayClip("SelectButton", 0);
                Collidingbackground_3 = true;
            }
            if (!isLeftClick && pendingToChange) {
                selectedBackground = "background_3.jpg";
                AM.PlayClip("ClickButton", 0);
                disabledBackground->GetTransform()->position = Vector2(1150, 260);
                disabledBackground->GetTransform()->scale = Vector2(1.2f, 1.2f);
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
            if (disabledEnemies->GetTransform()->position == enemies_1->GetTransform()->position)
                disabledEnemies->GetTransform()->scale = Vector2(1.4f, 1.4f);
            if (isLeftClick) {
                pendingToChange = true;
            }
            if (!Collidingenemies_1) {
                AM.PlayClip("SelectButton", 0);
                Collidingenemies_1 = true;
            }
            if (!isLeftClick && pendingToChange) {
                selectedEnemy = "enemy_1";
                AM.PlayClip("ClickButton", 0);
                disabledEnemies->GetTransform()->position = Vector2(650, 410);
                disabledEnemies->GetTransform()->scale = Vector2(1.2f, 1.2f);
                pendingToChange = false;
            }
        }
        else {
            enemies_1->GetTransform()->scale = Vector2(1.0f, 1.0f);
            disabledEnemies->GetTransform()->scale = Vector2(1.2f, 1.2f);
            Collidingenemies_1 = false;
        }

        if (IsMouseOverSprite(enemies_2, mousePos)) {
            enemies_2->GetTransform()->scale = Vector2(1.2f, 1.2f);
            if (disabledEnemies->GetTransform()->position == enemies_2->GetTransform()->position)
                disabledEnemies->GetTransform()->scale = Vector2(1.4f, 1.4f);
            if (isLeftClick) {
                pendingToChange = true;
            }
            if (!Collidingenemies_2) {
                AM.PlayClip("SelectButton", 0);
                Collidingenemies_2 = true;
            }
            if (!isLeftClick && pendingToChange) {
                selectedEnemy = "enemy_2";
                AM.PlayClip("ClickButton", 0);
                disabledEnemies->GetTransform()->position = Vector2(900, 410);
                disabledEnemies->GetTransform()->scale = Vector2(1.2f, 1.2f);
                pendingToChange = false;
            }
        }
        else {
            enemies_2->GetTransform()->scale = Vector2(1.0f, 1.0f);
            Collidingenemies_2 = false;
        }

        if (IsMouseOverSprite(enemies_3, mousePos)) {
            enemies_3->GetTransform()->scale = Vector2(1.2f, 1.2f);
            if (disabledEnemies->GetTransform()->position == enemies_3->GetTransform()->position)
                disabledEnemies->GetTransform()->scale = Vector2(1.4f, 1.4f);
            if (isLeftClick) {
                pendingToChange = true;
            }
            if (!Collidingenemies_3) {
                AM.PlayClip("SelectButton", 0);
                Collidingenemies_3 = true;
            }
            if (!isLeftClick && pendingToChange) {
                selectedEnemy = "enemy_3";
                AM.PlayClip("ClickButton", 0);
                disabledEnemies->GetTransform()->position = Vector2(1150, 410);
                disabledEnemies->GetTransform()->scale = Vector2(1.2f, 1.2f);
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
            if (disabledVFX->GetTransform()->position == VFX_1->GetTransform()->position)
                disabledVFX->GetTransform()->scale = Vector2(1.4f, 1.4f);
            if (isLeftClick) {
                pendingToChange = true;
            }
            if (!CollidingVFX_1) {
                AM.PlayClip("SelectButton", 0);
                CollidingVFX_1 = true;
            }
            if (!isLeftClick && pendingToChange) {
                selectedVFX = "VFX_1";
                AM.PlayClip("ClickButton", 0);
                disabledVFX->GetTransform()->position = Vector2(650, 560);
                disabledVFX->GetTransform()->scale = Vector2(1.2f, 1.2f);
                pendingToChange = false;
            }
        }
        else {
            VFX_1->GetTransform()->scale = Vector2(1.0f, 1.0f);
            disabledVFX->GetTransform()->scale = Vector2(1.2f, 1.2f);
            CollidingVFX_1 = false;
        }

        if (IsMouseOverSprite(VFX_2, mousePos)) {
            VFX_2->GetTransform()->scale = Vector2(1.2f, 1.2f);
            if (disabledVFX->GetTransform()->position == VFX_2->GetTransform()->position)
                disabledVFX->GetTransform()->scale = Vector2(1.4f, 1.4f);
            if (isLeftClick) {
                pendingToChange = true;
            }
            if (!CollidingVFX_2) {
                AM.PlayClip("SelectButton", 0);
                CollidingVFX_2 = true;
            }
            if (!isLeftClick && pendingToChange) {
                selectedVFX = "VFX_2";
                AM.PlayClip("ClickButton", 0);
                disabledVFX->GetTransform()->position = Vector2(900, 560);
                disabledVFX->GetTransform()->scale = Vector2(1.2f, 1.2f);
                pendingToChange = false;
            }
        }
        else {
            VFX_2->GetTransform()->scale = Vector2(1.0f, 1.0f);
            CollidingVFX_2 = false;
        }

        if (IsMouseOverSprite(VFX_3, mousePos)) {
            VFX_3->GetTransform()->scale = Vector2(1.2f, 1.2f);
            if (disabledVFX->GetTransform()->position == VFX_3->GetTransform()->position)
                disabledVFX->GetTransform()->scale = Vector2(1.4f, 1.4f);
            if (isLeftClick) {
                pendingToChange = true;
            }
            if (!CollidingVFX_3) {
                AM.PlayClip("SelectButton", 0);
                CollidingVFX_3 = true;
            }
            if (!isLeftClick && pendingToChange) {
                selectedVFX = "VFX_3";
                AM.PlayClip("ClickButton", 0);
                disabledVFX->GetTransform()->position = Vector2(1150, 560);
                disabledVFX->GetTransform()->scale = Vector2(1.2f, 1.2f);
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

    static std::string GetSelectedBackground() { return selectedBackground; }
    std::string GetSelectedEnemy() const { return selectedEnemy; }
    std::string GetSelectedVFX() const { return selectedVFX; }

};
std::string SpriteSelector::selectedBackground = "background_1.jpg";
std::string SpriteSelector::selectedEnemy = "enemies_1";
std::string SpriteSelector::selectedVFX = "VFX_1";