#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Math.hpp"

RenderWindow::RenderWindow(const char* title, int width, int height)
    : window(nullptr), renderer(nullptr)
{
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);

    if (window == nullptr) {
        printf("Couldn't create window. [Error]: %s\n", SDL_GetError());
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

SDL_Texture* RenderWindow::loadTexture(const char* path) {
    SDL_Texture* texture = nullptr;

    if (!strcmp(path, "")) {
        printf("Please provide a path to texture!\n");
        return texture;
    }

    texture = IMG_LoadTexture(renderer, path);

    if (texture == nullptr) {
        printf("Texture could not be loaded. [Error]: %s\n", IMG_GetError());
    }

    return texture;
}

void RenderWindow::clear() {
    SDL_RenderClear(renderer);
}

void RenderWindow::render(SDL_Texture* texture, int x, int y, int w, int h) {
    SDL_Rect src = { 0, 0, w, h };
    SDL_Rect dst = { x, y, w, h };
    SDL_RenderCopy(renderer, texture, &src, &dst);
}

void RenderWindow::render(Entity* e) {
    vector2<float> pos = e->getPosition();
    SDL_Rect src = e->getSrc();
    SDL_Rect dst = { (int) pos.getX(), (int) pos.getY(), src.w, src.h };
    SDL_RenderCopy(renderer, e->getTexture(), &src, &dst);
}

void RenderWindow::render(TTF_Font* font, const char* text, SDL_Color color, vector2<float> position)
{
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect src = { 0, 0, surface->w, surface->h };
    SDL_Rect dst = { (int) position.getX(), (int) position.getY(), src.w, src.h };
    SDL_RenderCopy(renderer, texture, &src, &dst);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}


void RenderWindow::display() {
    SDL_RenderPresent(renderer);
}

RenderWindow::~RenderWindow() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
}
