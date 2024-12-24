#pragma once
#include "Scene.h"
#include "TextObject.h"
#include "InputManager.h"
#include "SceneManager.h"

class MainMenu : public Scene
{
private:
    
    TextObject* buttonPlay;
    TextObject* buttonSelectSprites;
    TextObject* buttonCheckRanking;
    TextObject* buttonAudio;
    TextObject* buttonExit;

    TextObject* AudioOn;
    TextObject* AudioOff;

    bool buttonPlayColliding = false;
    bool buttonSelectSpritesColliding = false;
    bool buttonCheckRankingColliding = false;
    bool buttonAudioColliding = false;
    bool buttonExitColliding = false;

    int selectedOption = 0;

    SDL_Color normalColor = { 255, 255, 255, 255 }; 
    SDL_Color selectedColor = { 255, 0, 0, 255 }; 

    bool isLeftClick = false;
    bool pendingToChange = false;

public:
    MainMenu() = default;

    void OnEnter() override {
        selectedOption = 0;

        buttonPlay = new TextObject("Play");
        buttonPlay->SetColor(selectedColor);
        buttonPlay->GetTransform()->scale = Vector2(1.0f, 1.0f);
        float halfButtonPlay = buttonPlay->GetSourceRect().w * buttonPlay->GetTransform()->scale.x * 0.5f;
        buttonPlay->GetTransform()->position = Vector2((RM->WINDOW_WIDTH / 2) - halfButtonPlay, 200);
        SPAWN.SpawnObject(buttonPlay);

        buttonSelectSprites = new TextObject("Select Sprites");
        buttonSelectSprites->SetColor(normalColor);
        buttonPlay->GetTransform()->scale = Vector2(1.0f, 1.0f);
        float halfButtonSelectSprites = buttonSelectSprites->GetSourceRect().w * buttonSelectSprites->GetTransform()->scale.x * 0.5f;
        buttonSelectSprites->GetTransform()->position = Vector2((RM->WINDOW_WIDTH / 2) - halfButtonSelectSprites, 270);
        SPAWN.SpawnObject(buttonSelectSprites);

        buttonCheckRanking = new TextObject("Check Ranking");
        buttonCheckRanking->SetColor(normalColor);
        buttonPlay->GetTransform()->scale = Vector2(1.0f, 1.0f);
        float halfButtonCheckRanking = buttonCheckRanking->GetSourceRect().w * buttonCheckRanking->GetTransform()->scale.x * 0.5f;
        buttonCheckRanking->GetTransform()->position = Vector2((RM->WINDOW_WIDTH / 2) - halfButtonCheckRanking, 340);
        SPAWN.SpawnObject(buttonCheckRanking);

        buttonAudio = new TextObject("Audio");
        buttonAudio->SetColor(normalColor);
        buttonPlay->GetTransform()->scale = Vector2(1.0f, 1.0f);
        float halfButtonAudio = buttonAudio->GetSourceRect().w * buttonAudio->GetTransform()->scale.x * 0.5f;
        buttonAudio->GetTransform()->position = Vector2((RM->WINDOW_WIDTH / 2) - halfButtonAudio, 410);
        SPAWN.SpawnObject(buttonAudio);

        buttonExit = new TextObject("Exit");
        buttonExit->SetColor(normalColor);
        buttonPlay->GetTransform()->scale = Vector2(1.0f, 1.0f);
        float halfButtonExit = buttonExit->GetSourceRect().w * buttonExit->GetTransform()->scale.x * 0.5f;
        buttonExit->GetTransform()->position = Vector2((RM->WINDOW_WIDTH / 2) - halfButtonExit, 520);
        SPAWN.SpawnObject(buttonExit);

        //-------------------------------AUDIO-------------------------------//
        AudioOn = new TextObject("On");
        AudioOn->SetColor(normalColor);
        AudioOn->GetTransform()->scale = Vector2(1.0f, 1.0f);
        AudioOn->GetTransform()->position = Vector2((RM->WINDOW_WIDTH / 2) - halfButtonAudio, 450);
        AudioOn->SetColor(selectedColor);
        SPAWN.SpawnObject(AudioOn);

        AudioOff = new TextObject("Off");
        AudioOff->SetColor(normalColor);
        AudioOff->GetTransform()->scale = Vector2(1.0f, 1.0f);
        AudioOff->GetTransform()->position = Vector2((RM->WINDOW_WIDTH / 2)- halfButtonAudio + 50, 450);
        SPAWN.SpawnObject(AudioOff);
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

        if(!IsMouseOverButton(buttonPlay, mousePos) && !IsMouseOverButton(buttonSelectSprites, mousePos) && !IsMouseOverButton(buttonAudio, mousePos) && !IsMouseOverButton(buttonCheckRanking, mousePos))
            pendingToChange = false;

        if (IsMouseOverButton(buttonPlay, mousePos)) {
            buttonPlay->SetColor(selectedColor);
            if (isLeftClick) {
                pendingToChange = true;
            }
            if (!buttonPlayColliding) {
                AM.PlayClip("SelectButton", 0);
                buttonPlayColliding = true;
            }
            if (!isLeftClick && pendingToChange) {
                SM.SetNextScene("PlayMenu");
                AM.PlayClip("ClickButton", 0);
                pendingToChange = false;
            }
        }
        else {
            buttonPlay->SetColor(normalColor);
            buttonPlayColliding = false;
        }


        if (IsMouseOverButton(buttonSelectSprites, mousePos)) {
            buttonSelectSprites->SetColor(selectedColor);
            if (isLeftClick) {
                pendingToChange = true;
            }
            if (!buttonSelectSpritesColliding) {
                AM.PlayClip("SelectButton", 0);
                buttonSelectSpritesColliding = true;
            }
            if (!isLeftClick && pendingToChange) {
                SM.SetNextScene("SpriteSelector");
                AM.PlayClip("ClickButton", 0);
                pendingToChange = false;
            }
        }
        else {
            buttonSelectSprites->SetColor(normalColor);
            buttonSelectSpritesColliding = false;
        }


        if (IsMouseOverButton(buttonCheckRanking, mousePos)) {
            buttonCheckRanking->SetColor(selectedColor);
            if (isLeftClick) {
                pendingToChange = true;
            }
            if (!buttonCheckRankingColliding) {
                AM.PlayClip("SelectButton", 0);
                buttonCheckRankingColliding = true;
            }
            if (!isLeftClick && pendingToChange) {
                SM.SetNextScene("Ranking");
                AM.PlayClip("ClickButton", 0);
                pendingToChange = false;
            }
        }
        else {
            buttonCheckRanking->SetColor(normalColor);
            buttonCheckRankingColliding = false;
        }


        if (IsMouseOverButton(buttonAudio, mousePos)) {
            buttonAudio->SetColor(selectedColor);
            if (isLeftClick) {
                pendingToChange = true;
            }
            if (!buttonAudioColliding) {
                AM.PlayClip("SelectButton", 0);
                buttonAudioColliding = true;
            }
            if (!isLeftClick && pendingToChange) {
                SM.SetNextScene("CheckRanking");
                AM.PlayClip("ClickButton", 0);
                pendingToChange = false;
            }
        }
        else {
            buttonAudio->SetColor(normalColor);
            buttonAudioColliding = false;
        }

        if (IsMouseOverButton(AudioOn, mousePos)) {
            if (isLeftClick) {
                AudioOn->SetColor(selectedColor);
                AudioOff->SetColor(normalColor);
                //AM.PlayClip("ClickButton", 0);
                AM.Unmute();
            }
        }

        if (IsMouseOverButton(AudioOff, mousePos)) {
            if (isLeftClick) {
                AudioOff->SetColor(selectedColor);
                AudioOn->SetColor(normalColor);
                //AM.PlayClip("ClickButton", 0);
                AM.Mute();
            }
        }


        if (IsMouseOverButton(buttonExit, mousePos)) {
            buttonExit->SetColor(selectedColor);
            if (isLeftClick) {
                //exit(0);
            }
            if (buttonExitColliding == false) {
                AM.PlayClip("SelectButton", 0);
                buttonExitColliding = true;
            }
        }
        else {
            buttonExit->SetColor(normalColor);
            buttonExitColliding = false;
        }

        Scene::Update();
    }

    void Render() override {
        Scene::Render();
    }

    ~MainMenu() {
        delete buttonPlay;
        delete buttonSelectSprites;
        delete buttonCheckRanking;
        delete buttonAudio;
        delete buttonExit;
        delete AudioOn;
        delete AudioOff;
    }
};