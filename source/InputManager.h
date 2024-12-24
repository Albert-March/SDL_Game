#pragma once
#pragma once
#include <SDL.h>
#include <queue>
#include <unordered_map>
#include "SceneManager.h"

#define Input InputManager::Instance()

enum KeyState { EMPTY, DOWN, UP, HOLD, RELEASED };

class InputManager
{
private:
    int mouseX, mouseY;
    bool leftClick;


    std::unordered_map<Sint32, KeyState> keyReference;

    InputManager()
    {
        SDL_GetMouseState(&mouseX, &mouseY);
    }

    InputManager(const InputManager& im) = delete;
    InputManager& operator=(const InputManager& val) = delete;

public:
    static InputManager& Instance()
    {
        static InputManager instance;
        return instance;
    }

    bool Listen()
    {

        //Update the keys from the previous frame
        for (std::unordered_map<Sint32, KeyState>::iterator it = keyReference.begin(); it != keyReference.end(); it++) 
        {
            if (it->second == DOWN)
                it->second = HOLD;
            else if (it->second == UP)
                it->second = RELEASED;
        }

        SDL_GetMouseState(&mouseX, &mouseY);

        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            switch (event.type) {
            case SDL_QUIT:
                return true;

            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT)
                    leftClick = true;
                break;

            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT)
                    leftClick = false;
                break;

            case SDL_KEYDOWN:
                if (keyReference[event.key.keysym.sym] != HOLD)
                    keyReference[event.key.keysym.sym] = DOWN;

                if (SM.GetCurrentScene()) {
                    SM.GetCurrentScene()->HandleTextInput(event);
                }
                break;

            case SDL_KEYUP:
                keyReference[event.key.keysym.sym] = UP;
                break;

            case SDL_TEXTINPUT:
                if (SM.GetCurrentScene()) {
                    SM.GetCurrentScene()->HandleTextInput(event);
                }
                break;

            default:
                break;
            }
        }
        return false;

    }
    inline int GetMouseX()const { return mouseX; }
    inline int GetMouseY() const { return mouseY; }
    inline bool GetLeftClick() const { return leftClick; }
    inline bool GetEvent(Sint32 input, KeyState inputValue)
    {
        return keyReference[input] == inputValue;
    }
};