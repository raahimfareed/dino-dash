#pragma once
#include <vector>

#include <SDL2/SDL.h>

#include "Entity.hpp"
#include "Math.hpp"
class Spike {
public:
    static Entity create(SDL_Texture* texture, SDL_Rect src, vector2<float> position);
    static void spawn(std::vector<Entity>& spikes, SDL_Texture* texture);
    static void update(std::vector<Entity>& spikes, float deltaTime);
    static void remove(std::vector<Entity>& spikes);
    static unsigned int random();
    static bool isColliding(Entity& entity, std::vector<Entity>& spikes);
    static void reset(std::vector<Entity>& spikes);

public:
    static float xVelocity;
};
