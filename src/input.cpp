#include <SDL2/SDL.h>
#include <map>

#include "Input.hpp"

std::map<SDL_Keycode, bool> Input::mpKeyState;
std::map<Uint8, bool> Input::mpMouseState;

void Input::handleKeyPress(SDL_Event &rEvent)
{
    mpKeyState[rEvent.key.keysym.sym] = true;
}

void Input::handleKeyRelease(SDL_Event &rEvent)
{
    mpKeyState[rEvent.key.keysym.sym] = false;
}

void Input::handleMouseClick(SDL_Event &rEvent)
{
    mpMouseState[rEvent.button.button] = true;
}

void Input::handleMouseRelease(SDL_Event &rEvent)
{
    mpMouseState[rEvent.button.button] = false;
}

bool Input::isPressed(const SDL_Keycode key)
{
    if (mpKeyState.count(key))
    {
        return mpKeyState[key];
    }

    return false;
}

bool Input::isClicked(const Uint8 key)
{
    if (mpMouseState.count(key))
    {
        return mpMouseState[key];
    }

    return false;
}
