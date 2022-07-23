#pragma once
#include <SDL2/SDL.h>

#include <map>

struct Input
{
    static void handleKeyPress(SDL_Event &rEvent);
    static void handleKeyRelease(SDL_Event &rEvent);
    static void handleMouseClick(SDL_Event &rEvent);
    static void handleMouseRelease(SDL_Event &rEvent);
    static bool isPressed(const SDL_Keycode key);
    static bool isClicked(const Uint8 key);

    static std::map<SDL_Keycode, bool> mpKeyState;
    static std::map<Uint8, bool> mpMouseState;
};