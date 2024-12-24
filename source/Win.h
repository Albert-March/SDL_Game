#pragma once
#include "Scene.h"
#include "TextObject.h"
#include "InputManager.h"
#include "SceneManager.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <fstream>

struct ScoreEntry {
    std::string playerName = "";
    int score = 0;
    int gameMode = 0;
};

class Win : public Scene {
private:
    TextObject* WinText;
    TextObject* NameInputText;
    TextObject* AcceptButton;
    TextObject* AlertText;

    std::string playerName = "";
    bool isTyping = false;

    bool isLeftClick = false;
    bool pendingToChange = false;
    bool buttonColliding = false;

    SDL_Color normalColor = { 255, 255, 255, 255 };
    SDL_Color selectedColor = { 255, 0, 0, 255 };

    int playerScore;
    int gameMode;

    bool newRecord;
    bool inTheList;

public:
    Win() = default;

    void OnEnter() override {
        SDL_StartTextInput();

        WinText = new TextObject("YOU WIN!");
        WinText->SetColor(selectedColor);
        WinText->GetTransform()->scale = Vector2(2.f, 2.f);
        WinText->GetTransform()->position = Vector2((RM->WINDOW_WIDTH / 2) - 200, 100);
        SPAWN.SpawnObject(WinText);

        NameInputText = new TextObject("Enter your name: ");
        NameInputText->SetColor(normalColor);
        NameInputText->GetTransform()->scale = Vector2(1.5f, 1.5f);
        NameInputText->GetTransform()->position = Vector2((RM->WINDOW_WIDTH / 2) - 200, 200);
        SPAWN.SpawnObject(NameInputText);

        AcceptButton = new TextObject("Accept");
        AcceptButton->SetColor(normalColor);
        AcceptButton->GetTransform()->scale = Vector2(2.f, 2.f);
        AcceptButton->GetTransform()->position = Vector2((RM->WINDOW_WIDTH / 2) - 50, 300);
        SPAWN.SpawnObject(AcceptButton);

        newRecord = false;
        inTheList = false;
    }

    void SortScores(std::vector<ScoreEntry>& scores) {
        for (size_t i = 0; i < scores.size(); i++) {
            for (size_t j = i + 1; j < scores.size(); j++) {
                if (scores[j].score > scores[i].score) {
                    ScoreEntry temp = scores[i];
                    scores[i] = scores[j];
                    scores[j] = temp;
                }
            }
        }
    }

    void SaveScore(const std::string& playerName, int playerScore, int gameMode) {
        std::map<int, std::vector<ScoreEntry>> scoresByMode;

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

        ScoreEntry newEntry;
        newEntry.playerName = playerName;
        newEntry.score = playerScore;
        newEntry.gameMode = gameMode;

        scoresByMode[gameMode].push_back(newEntry);

        SortScores(scoresByMode[gameMode]);

        if (scoresByMode[gameMode].size() > 10 && newEntry.score > scoresByMode[gameMode][10].score) {
            std::cout << "U are in the list";
            inTheList = true;
        }

        if (!scoresByMode[gameMode].empty() && newEntry.score == scoresByMode[gameMode][0].score) {
            std::cout << "NEW RECORD!!";
            newRecord = true;
        }

        if (scoresByMode[gameMode].size() > 10) {
            scoresByMode[gameMode].resize(10);
        }

        std::ofstream outFile("ranking.dat", std::ios::binary | std::ios::trunc);
        if (outFile.is_open()) {
            int totalEntries = 0;
            for (const auto& pair : scoresByMode) {
                totalEntries += pair.second.size();
            }

            outFile.write(reinterpret_cast<const char*>(&totalEntries), sizeof(int));

            for (const auto& pair : scoresByMode) {
                for (const auto& entry : pair.second) {
                    size_t nameSize = entry.playerName.size();
                    outFile.write(reinterpret_cast<const char*>(&entry.gameMode), sizeof(int));
                    outFile.write(reinterpret_cast<const char*>(&nameSize), sizeof(size_t));
                    outFile.write(entry.playerName.c_str(), nameSize);
                    outFile.write(reinterpret_cast<const char*>(&entry.score), sizeof(int));
                }
            }
            outFile.close();
        }
    }

    bool IsMouseOverButton(TextObject* button, Vector2 mousePos) {
        button->Update();
        SDL_Rect destRect = button->GetDestRect();

        return (mousePos.x >= destRect.x && mousePos.x <= destRect.x + destRect.w &&
            mousePos.y >= destRect.y && mousePos.y <= destRect.y + destRect.h);
    }

    void HandleTextInput(SDL_Event& event) override {
        if (event.type == SDL_TEXTINPUT) {
            playerName += event.text.text;
            NameInputText->SetText(" " + playerName); //" " perque no peti al eliminar tot el nom
            std::cout << "Leter " << event.text.text << std::endl;
        }

        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_BACKSPACE && !playerName.empty()) {
                playerName.pop_back();
                NameInputText->SetText(" " + playerName);
                std::cout << "BACKSPACE" << std::endl;
            }
        }
    }

    void Update() override {
        Vector2 mousePos = Vector2(Input.GetMouseX(), Input.GetMouseY());
        isLeftClick = Input.GetLeftClick();

        if (IsMouseOverButton(AcceptButton, mousePos)) {
            AcceptButton->SetColor(selectedColor);
            if (isLeftClick) {
                pendingToChange = true;
            }
            if (!buttonColliding) {
                AM.PlayClip("SelectButton", 0);
                buttonColliding = true;
            }
            if (!isLeftClick && pendingToChange) {
                if (playerName.length() >= 1 && playerName.length() <= 10) {
                    std::cout << "Final Name: " << playerName << std::endl;
                    AM.PlayClip("ClickButton", 0);

                    SaveScore(playerName, playerScore, gameMode);

                    if(inTheList){
                        SM.SetNextScene("Ranking");
                    }
                    else if (newRecord) {
                        SM.SetNextScene("Ranking");
                    }
                    else {
                        SM.SetNextScene("Main Menu");
                    }
                    playerName = "";
                    pendingToChange = false;
                }
                else {
                    std::string mesage;
                    if (playerName.length() < 1) {
                        mesage = "The name cannot have 0 characters";
                    }
                    if (playerName.length() > 10) {
                        mesage = "The name cannot have more than 10 characters";
                    }
                    AlertText = new TextObject(mesage);
                    AlertText->SetColor(selectedColor);
                    AlertText->GetTransform()->scale = Vector2(1.f, 1.f);
                    AlertText->GetTransform()->position = Vector2((RM->WINDOW_WIDTH / 2) - 200, 600);
                    SPAWN.SpawnObject(AlertText);
                    pendingToChange = false;
                }
            }
        }
        else {
            AcceptButton->SetColor(normalColor);
            buttonColliding = false;
        }

        Scene::Update();
    }

    void Render() override {
        Scene::Render();
    }

    ~Win() {
        SDL_StopTextInput();
        delete WinText;
        delete NameInputText;
        delete AcceptButton;
        delete AlertText;
    }

    void SetScoreAndMode(int newScore, int newGameMode) {
        playerScore = newScore;
        gameMode = newGameMode;
    }
};









