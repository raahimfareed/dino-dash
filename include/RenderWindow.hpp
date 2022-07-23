#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Entity.hpp"
#include "Math.hpp"

class RenderWindow {
public:
    RenderWindow(const char* title, int width, int height);
    SDL_Texture* loadTexture(const char* path);
    void clear();
    void render(SDL_Texture* texture, int x, int y, int w, int h);
    void render(Entity* e);
    void render(TTF_Font* font, const char* text, SDL_Color color, vector2<float> position);
    void display();
    ~RenderWindow();
private:
    SDL_Window *window;
    SDL_Renderer *renderer;
};
