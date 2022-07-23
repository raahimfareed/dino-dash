#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Math.hpp"

class Entity {
public:
    Entity(SDL_Texture* texture, SDL_Rect src, vector2<float> position);
    SDL_Texture* getTexture();
    SDL_Rect getSrc();
    vector2<float> getPosition();

    void setPosition(float x, float y);
    void setPosition(vector2<float> position);

    void setX(float x);
    void setY(float y);

protected:
    SDL_Texture* texture;
    SDL_Rect src;
    vector2<float> position;
};