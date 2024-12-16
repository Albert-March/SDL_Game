#pragma once
#include "Scene.h"
#include "TextObject.h"
#include "InputManager.h"
#include "SceneManager.h"

class MainMenu : public Scene
{
   private:
        TextObject* buttonTanks;
        TextObject* buttonSwatter;
        TextObject* buttonSpaceInvaders;


        TextRenderer* tr; 


        int selectedOption = 0;

        SDL_Color normalColor = { 255, 255, 255, 255 }; 
        SDL_Color selectedColor = { 255, 0, 0, 255 }; 

    public:
        MainMenu() = default;

        void OnEnter() override {
            buttonTanks = new TextObject("Tanks Game");
            buttonTanks->SetColor(selectedColor);
            buttonTanks->GetTransform()->position = Vector2(RM->WINDOW_WIDTH / 2, 200);
            buttonTanks->GetTransform()->scale = Vector2(1.2f, 1.2f);
            SPAWN.SpawnObject(buttonTanks);

            buttonSwatter = new TextObject("Swatter Game");
            buttonSwatter->SetColor(normalColor);
            buttonSwatter->GetTransform()->position = Vector2(RM->WINDOW_WIDTH / 2, 300);
            buttonSwatter->GetTransform()->scale = Vector2(1.2f, 1.2f);
            SPAWN.SpawnObject(buttonSwatter);

            buttonSpaceInvaders = new TextObject("Space Invaders Game");
            buttonSpaceInvaders->SetColor(normalColor);
            buttonSpaceInvaders->GetTransform()->position = Vector2(RM->WINDOW_WIDTH / 2, 400);
            buttonSpaceInvaders->GetTransform()->scale = Vector2(1.2f, 1.2f);
            SPAWN.SpawnObject(buttonSpaceInvaders);

            UpdateButtonColors();

        }

        void Update() override {
            // Navegación del menú con teclas de flecha
            if (Input.GetEvent(SDLK_UP, DOWN)) {
                selectedOption = (selectedOption - 1 + 3) % 3; // Mover hacia arriba
                UpdateButtonColors();
            }
            if (Input.GetEvent(SDLK_DOWN, DOWN)) {
                selectedOption = (selectedOption + 1) % 3; // Mover hacia abajo
                UpdateButtonColors();
            }

            // Selección del botón con Enter
            if (Input.GetEvent(SDLK_RETURN, DOWN)) {
                switch (selectedOption) {
                case 0:
                    SM.SetNextScene("Tanks"); // Cambiar a la escena Tanks
                    break;
                case 1:
                    SM.SetNextScene("Swatter"); // Cambiar a la escena Swatter
                    break;
                case 2:
                    SM.SetNextScene("SpaceInvaders"); // Cambiar a la escena SpaceInvaders
                    break;
                }
            }
            Scene::Update();
        }

        void Render() override {
            Scene::Render();
        }

        ~MainMenu() {
            // Liberar memoria
            delete buttonTanks;
            delete buttonSwatter;
            delete buttonSpaceInvaders;
        }

private:
    void UpdateButtonColors() {
        // Cambiar el color de los botones según la opción seleccionada
        buttonTanks->SetColor(selectedOption == 0 ? selectedColor : normalColor);
        buttonSwatter->SetColor(selectedOption == 1 ? selectedColor : normalColor);
        buttonSpaceInvaders->SetColor(selectedOption == 2 ? selectedColor : normalColor);
    }

};