#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <cstdint>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "RenderWindow.hpp"
#include "Config.hpp"
#include "Entity.hpp"
#include "Player.hpp"
#include "Math.hpp"
#include "Input.hpp"
#include "Spike.hpp"

bool init();
void destroy();
void reset();

enum class GameState {
    STARTSCREEN,
    PLAYING,
    DEATHSCREEN,
};

RenderWindow* gWindow = nullptr;

std::map<const char*, SDL_Texture*> gTextures;
std::map<const char*, TTF_Font*> gFonts;
std::map<const char*, Mix_Chunk*> gAudio;
Mix_Music* gBgMusic = nullptr;

std::vector<Entity> gEntities;
std::vector<Entity> gGroundTiles;
Player* gPlayer = nullptr;
GameState gState = GameState::STARTSCREEN;

int main(int argc, char** argv) {
    bool running = init();

    // My implementation of a independence to the framerate.
    std::uint64_t prevTicks = SDL_GetTicks64();
    std::uint64_t nowTicks = 0;
    float deltaTime = 0;

    while (running) {
        nowTicks = SDL_GetTicks64();
        deltaTime = (nowTicks - prevTicks) / 1000.f;
        prevTicks = nowTicks;

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_KEYDOWN:
                    Input::handleKeyPress(event);
                    break;
                case SDL_KEYUP:
                    Input::handleKeyRelease(event);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    Input::handleMouseClick(event);
                    break;
                case SDL_MOUSEBUTTONUP:
                    Input::handleMouseRelease(event);
                    break;
            }
        }

        if (Input::isPressed(SDLK_q)) {
            running = false;
        }

        if (Spike::isColliding(*gPlayer, gEntities)) {
            if (gState == GameState::PLAYING) {
                    Mix_PlayChannel(-1, gAudio["death"], 0);
            }
            gState = GameState::DEATHSCREEN;
        }

        if (gState == GameState::PLAYING) {
            gPlayer->update(deltaTime);
            Spike::spawn(gEntities, gTextures["spike"]);
            Spike::update(gEntities, deltaTime);
            Spike::remove(gEntities);

            if (Input::isPressed(SDLK_SPACE) && !gPlayer->isJumping() && gPlayer->onGround(gGroundTiles)) {
                Mix_PlayChannel(-1, gAudio["jump"], 0);
                gPlayer->jump();
            }
        }

        if (gState == GameState::STARTSCREEN) {
            if (Input::isPressed(SDLK_RETURN) && !gPlayer->isJumping() && gPlayer->onGround(gGroundTiles)) {
                Mix_PlayChannel(-1, gAudio["select"], 0);
                gState = GameState::PLAYING;
            }
        }

        if (gState == GameState::DEATHSCREEN) {
            if (Input::isPressed(SDLK_RETURN)) {
                reset();
            }
        }

        gWindow->clear();

        if (gState == GameState::STARTSCREEN) {
            gWindow->render(gFonts["default"], "Press [return] to start", {255, 255, 255, 255}, {64, (float)(Config::height - 128) / 2});
            gWindow->render(gFonts["small"], "Press [q] to quit", {158, 158, 158, 255}, {64, (float)(Config::height) / 2});
        }

        if (gState == GameState::DEATHSCREEN) {
            gWindow->render(gFonts["default"], "Game Over!", {255, 0, 0, 255}, {64, (float)(Config::height - 128) / 2});
            gWindow->render(gFonts["small"], "Press [return] to restart", {255, 255, 255, 255}, {64, (float)(Config::height) / 2});
        }

        if (gState == GameState::PLAYING) {
            gWindow->render(gFonts["small"], std::string("Score: " + std::to_string(gPlayer->getScore())).c_str() , {255, 255, 255, 255}, {64, 64});
        }

        if (gState == GameState::PLAYING) { 
            for (auto &e: gGroundTiles) {
                gWindow->render(&e);
            }
            for (auto &e: gEntities) {
                gWindow->render(&e);
            }
            gWindow->render(gPlayer);
        }
        gWindow->display();

    }

    destroy();
}

bool init() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) > 0) {
        printf("Couldn't init video! [Error]: %s\n", SDL_GetError());
        return false;
    }

    if (!IMG_Init(IMG_INIT_PNG)) {
        printf("Couldn't init video! [Error]: %s\n", IMG_GetError());
        return false;
    }

    if (TTF_Init() == -1) {
        printf("Couldn't init text! [Error]: %s\n", TTF_GetError());
        return false;
    }

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    gWindow = new RenderWindow(Config::title, Config::width, Config::height);

    if (gWindow == nullptr) {
        return false;
    }

    printf("Initialized window!\n");

    gTextures["ground-full"] = gWindow->loadTexture("assets/ground-1280x256.png");
    gTextures["player"] = gWindow->loadTexture("assets/player-32x32.png");
    gTextures["spike"] = gWindow->loadTexture("assets/spike-16x8.png");

    gFonts["default"] = TTF_OpenFont("assets/Sniglet-Regular.ttf", 64);
    gFonts["small"] = TTF_OpenFont("assets/Sniglet-Regular.ttf", 32);

    gAudio["jump"] = Mix_LoadWAV("assets/jump.wav");
    gAudio["death"] = Mix_LoadWAV("assets/hit.wav");
    gAudio["select"] = Mix_LoadWAV("assets/select.wav");

    // FIX: Not working
    // gBgMusic = Mix_LoadMUS("assets/bg.wav");
    // Mix_PlayMusic(gBgMusic, -1);

    gGroundTiles.push_back(Entity(gTextures["ground-full"], {0, 0, 1280, 256}, vector2<float>(0, 720-256)));

    gPlayer = new Player(gTextures["player"]);

    gEntities.push_back(Entity(gTextures["spike"], { 0, 0, 16, 8}, vector2<float>(0, 0)));


    return true;
}

void destroy() {
    printf("Clearing resources!\n");
    if (gWindow) {
        delete gWindow;
    }
    if (gPlayer) {
        delete gPlayer;
    }
    SDL_Quit();
}

void reset() {
    gState = GameState::STARTSCREEN;
    gPlayer->reset();
    Spike::reset(gEntities);
}
