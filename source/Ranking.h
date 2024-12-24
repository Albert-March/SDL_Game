#pragma once
#include "Scene.h"
#include "TextObject.h"
#include "InputManager.h"
#include "SceneManager.h"

class Ranking : public Scene
{
private:
    TextObject* textRanking;
    TextObject* textSpaceInvaders;
    TextObject* textTank;
    TextObject* textSwatter;
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
    Ranking() = default;

    void OnEnter() override {
        selectedOption = 0;

        textRanking = new TextObject("Ranking");
        textRanking->GetTransform()->scale = Vector2(2.f, 2.f);
        float halftext = textRanking->GetSourceRect().w * textRanking->GetTransform()->scale.x * 0.5f;
        textRanking->GetTransform()->position = Vector2((RM->WINDOW_WIDTH / 2) - halftext, 130);
        SPAWN.SpawnObject(textRanking);

        textSpaceInvaders = new TextObject("Space Invaders");
        textSpaceInvaders->SetColor(normalColor);
        textSpaceInvaders->GetTransform()->scale = Vector2(1.f, 1.f);
        float halfSpaceInvaders = textSpaceInvaders->GetSourceRect().w * textSpaceInvaders->GetTransform()->scale.x * 0.5f;
        textSpaceInvaders->GetTransform()->position = Vector2((RM->WINDOW_WIDTH / 2) - halfSpaceInvaders - 400, 150);
        SPAWN.SpawnObject(textSpaceInvaders);

        std::string scoreTextSpaceInvaders = GetScoresAsString(0);
        textSpaceInvaders = new TextObject(scoreTextSpaceInvaders);
        textSpaceInvaders->SetColor(normalColor);
        textSpaceInvaders->GetTransform()->scale = Vector2(1.f, 1.f);
        textSpaceInvaders->GetTransform()->position = Vector2((RM->WINDOW_WIDTH / 2) - halfSpaceInvaders - 400, 200);
        SPAWN.SpawnObject(textSpaceInvaders);


        textTank = new TextObject("Tank");
        textTank->SetColor(normalColor);
        textTank->GetTransform()->scale = Vector2(1.f, 1.f);
        float halfTank = textTank->GetSourceRect().w * textTank->GetTransform()->scale.x * 0.5f;
        textTank->GetTransform()->position = Vector2((RM->WINDOW_WIDTH / 2) - halfTank, 150);
        SPAWN.SpawnObject(textTank);

        std::string scoreTextTank = GetScoresAsString(1);
        textTank = new TextObject(scoreTextTank);
        textTank->SetColor(normalColor);
        textTank->GetTransform()->scale = Vector2(1.f, 1.f);
        textTank->GetTransform()->position = Vector2((RM->WINDOW_WIDTH / 2) - halfTank, 200);
        SPAWN.SpawnObject(textTank); 
        
        
        textSwatter = new TextObject("Swatter");
        textSwatter->SetColor(normalColor);
        textSwatter->GetTransform()->scale = Vector2(1.f, 1.f);
        float halfSwatter = textSwatter->GetSourceRect().w * textSwatter->GetTransform()->scale.x * 0.5f;
        textSwatter->GetTransform()->position = Vector2((RM->WINDOW_WIDTH / 2) - halfSwatter +400, 150);
        SPAWN.SpawnObject(textSwatter);

        std::string scoreTextSwatter = GetScoresAsString(2);
        textSwatter = new TextObject(scoreTextSwatter);
        textSwatter->SetColor(normalColor);
        textSwatter->GetTransform()->scale = Vector2(1.f, 1.f);
        textSwatter->GetTransform()->position = Vector2((RM->WINDOW_WIDTH / 2) - halfSwatter + 400, 200);
        SPAWN.SpawnObject(textSwatter);


        buttonBack = new TextObject("Back");
        buttonBack->SetColor(normalColor);
        buttonBack->GetTransform()->scale = Vector2(1.f, 1.f);
        float halfButtonBack = buttonBack->GetSourceRect().w * buttonBack->GetTransform()->scale.x * 0.5f;
        buttonBack->GetTransform()->position = Vector2((RM->WINDOW_WIDTH / 2) - halfButtonBack, RM->WINDOW_HEIGHT - 100);
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

    std::string GetScoresAsString(int gameMode) {
        std::map<int, std::vector<ScoreEntry>> scoresByMode;
        std::string result = "";

        std::ifstream inFile("ranking.dat", std::ios::binary);
        if (inFile.is_open()) {
            int numEntries;
            inFile.read(reinterpret_cast<char*>(&numEntries), sizeof(int));

            for (int i = 0; i < numEntries; i++) {
                ScoreEntry entry;
                size_t nameSize;

                inFile.read(reinterpret_cast<char*>(&entry.gameMode), sizeof(int));
                inFile.read(reinterpret_cast<char*>(&nameSize), sizeof(size_t));
                entry.playerName.resize(nameSize);
                inFile.read(&entry.playerName[0], nameSize);
                inFile.read(reinterpret_cast<char*>(&entry.score), sizeof(int));

                scoresByMode[entry.gameMode].push_back(entry);
            }
            inFile.close();
        }

        if (scoresByMode.find(gameMode) != scoresByMode.end()) {
            int rank = 1;
            for (const auto& entry : scoresByMode[gameMode]) {
                result += entry.playerName + " - " + std::to_string(entry.score) + "\n";
                rank++;
            }
        }

        return result;
    }

    void Update() override {
        Vector2 mousePos = Vector2(Input.GetMouseX(), Input.GetMouseY());
        isLeftClick = Input.GetLeftClick();

        if (!IsMouseOverButton(buttonBack, mousePos))
            pendingToChange = false;

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

    ~Ranking() {
        delete textRanking;
        delete textSwatter;
        delete textSpaceInvaders;
        delete buttonBack;
    }
};